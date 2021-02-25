#include "Zone.h"
#include "../cwsdk.h"
#include "Block.h"

IntVector2 cube::Zone::ZoneCoordsFromDots(LongVector3 position) {
	int zone_x = pydiv(pydiv(position.x, cube::DOTS_PER_BLOCK), cube::BLOCKS_PER_ZONE);
	int zone_y = pydiv(pydiv(position.y, cube::DOTS_PER_BLOCK), cube::BLOCKS_PER_ZONE);
	return IntVector2(zone_x, zone_y);
}

IntVector2 cube::Zone::ZoneCoordsFromBlocks(int64_t x, int64_t y) {
	int zone_x = pydiv(x, cube::BLOCKS_PER_ZONE);
	int zone_y = pydiv(y, cube::BLOCKS_PER_ZONE);
	return IntVector2(zone_x, zone_y);
}
void cube::Zone::SetBlock(IntVector3 zone_position, cube::Block block, bool update) {
	// NOTE: Setting chunk.needs_remesh too often can cause a heap corruption during the rendering process.
	// I haven't figured out a solution to this yet, aside from performing the action on the same thread as the chunk remesh

	int fieldIndex = zone_position.x * cube::BLOCKS_PER_ZONE + zone_position.y;
	cube::Field* field = &this->fields[fieldIndex];

	int block_index = zone_position.z - field->base_z;
	int end_z = field->base_z + field->blocks.size();

	if (zone_position.z >= end_z) { //Too high
		block_index = zone_position.z - field->base_z;

		int old_count = field->blocks.size();
		field->blocks.resize(block_index + 1);
		int new_count = field->blocks.size();

		void* start_air = &field->blocks[old_count];
		int air_size = (new_count - old_count) * sizeof(cube::Block);
		memset(start_air, 0, air_size);

		field->blocks[block_index] = block;
	} 
	else if (zone_position.z < field->base_z) { //Too low
		int old_size = field->blocks.size() * sizeof(cube::Block);
		char* tmp_blocks = new char[old_size];
		memcpy(tmp_blocks, &field->blocks[0], old_size);

		int difference = field->base_z - zone_position.z;

		// Get interpolated blocks for those which are being created below base z
		cube::Block* filler_blocks = new cube::Block[difference];
		IntVector3 fill_location = zone_position;
		for (int i = 0; i < difference; i++) {
			filler_blocks[i] = this->GetBlockInterpolated(fill_location);
			fill_location.z++;
		}

		int required_blocks = field->blocks.size() + difference;

		field->blocks.resize(required_blocks);

		//memset(&field->blocks[0], 0, difference * sizeof(cube::Block)); //Air
		
		memcpy(&field->blocks[0], filler_blocks, difference * sizeof(cube::Block));
		memcpy(&field->blocks[difference], tmp_blocks, old_size);
		

		field->blocks[0] = block;

		field->base_z -= difference;

		delete[] tmp_blocks;
		delete[] filler_blocks;
	}
	else {
		int block_index = zone_position.z - field->base_z;
		field->blocks[block_index] = block;
	}

	if (update) {
		this->chunk.Remesh();
	}
}

cube::Block* cube::Zone::GetBlock(IntVector3 zone_position) {
	int fieldIndex = zone_position.x * cube::BLOCKS_PER_ZONE + zone_position.y;
	cube::Field* field = &this->fields[fieldIndex];
	if (zone_position.z < field->base_z) {
		return nullptr;
	}

	int block_index = zone_position.z - field->base_z;

	if (block_index >= field->blocks.size()) {
		return nullptr;
	}

	return &field->blocks[block_index];
}

cube::Block cube::Zone::GetBlockInterpolated(IntVector3 zone_position) {
	int fieldIndex = zone_position.x * cube::BLOCKS_PER_ZONE + zone_position.y;
	cube::Field* field = &this->fields[fieldIndex];

	if (zone_position.z < field->base_z) {
		cube::Block block;

		// This is how blocks below the base-z are interpolated for the renderer. It's black magic to me!
		int block_x_coord = this->position.x * cube::BLOCKS_PER_ZONE + zone_position.x;
		int block_y_coord = this->position.y * cube::BLOCKS_PER_ZONE + zone_position.y;

		float interpolation_x_minus_1 = ((float(*)(cube::World*, int, int))CWOffset(0x35EA0))(this->world, block_x_coord - 1, block_y_coord);
		float interpolation_x_plus_1 = ((float(*)(cube::World*, int, int))CWOffset(0x35EA0))(this->world, block_x_coord + 1, block_y_coord);
		float interpolation_y_minus_1 = ((float(*)(cube::World*, int, int))CWOffset(0x35EA0))(this->world, block_x_coord, block_y_coord - 1);
		float interpolation_y_plus_1 = ((float(*)(cube::World*, int, int))CWOffset(0x35EA0))(this->world, block_x_coord, block_y_coord + 1);
		cube::BlockProperties<float> block_properties;
		((cube::BlockProperties<float> * (*)(cube::World*, cube::BlockProperties<float>*, signed int, signed int, signed int, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float))
			CWOffset(0x2D8E00))
			(this->world,
			 &block_properties,
			 block_x_coord,
			 block_y_coord,
			 zone_position.z,
			 field->field_8,
			 interpolation_x_minus_1,
			 interpolation_x_plus_1,
			 interpolation_y_minus_1,
			 interpolation_y_plus_1,
			 field->field_14,
			 field->field_C,
			 field->field_10,
			 field->field_28,
			 0.0,
			 field->field_38,
			 field->field_18,
			 field->field_1C,
			 field->field_20,
			 field->field_30,
			 field->field_34);
		((void(*)(cube::Block*, cube::BlockProperties<float>*))CWOffset(0xBA820))(&block, &block_properties);

		block.Half(block_properties);

		return block;
	}

	int block_index = zone_position.z - field->base_z;

	if (block_index >= field->blocks.size()) {
		// Air or water
		cube::Block block;
		block.red = 255;
		block.green = 255;
		block.blue = 255;
		block.field_3 = 0;
		block.type = (zone_position.z > 0) ? cube::Block::Type::Air : cube::Block::Type::Water;
		block.breakable = 0;
		return block;
	}

	// turn sub-0 air blocks into water
	cube::Block block = field->blocks[block_index];
	if ( (zone_position.z <= 0) && (block.type == cube::Block::Type::Air) ) {
		block.type = cube::Block::Type::Water;
	}

	return block;
}