#include "World.h"
#include "Zone.h"
#include "constants.h"
#include "../common/Vector3.h"
#include "../cwsdk.h"

cube::Zone* cube::World::GetZone(IntVector2 position) {
	try {
		return this->zones.at(position);
	}
	catch (const std::out_of_range & oor) {
		return nullptr;
	}
	
}
cube::Zone* cube::World::GetZone(int x, int y) {
	IntVector2 position(x, y);
	return this->GetZone(position);
}
void cube::World::SetBlock(LongVector3 block_pos, Block block, bool update) {
	IntVector2 zonePos = cube::Zone::ZoneCoordsFromBlocks(block_pos.x, block_pos.y);
	cube::Zone* zone = this->GetZone(zonePos);
	if (!zone) return;
	IntVector3 zoneBlockPos(pymod(block_pos.x, cube::BLOCKS_PER_ZONE), pymod(block_pos.y, cube::BLOCKS_PER_ZONE), block_pos.z);
	zone->SetBlock(zoneBlockPos, block, update);

	LongVector3 blockInZonePos = LongVector3(pymod(block_pos.x, cube::BLOCKS_PER_ZONE), pymod(block_pos.y, cube::BLOCKS_PER_ZONE), block_pos.z);

	if (update) {
		//Update adjacent chunks if needed
		if (blockInZonePos.x == 0) {
			zone = this->GetZone(IntVector2(zonePos.x - 1, zonePos.y));
			if (zone) zone->chunk.Remesh();
		} else if (blockInZonePos.x == cube::BLOCKS_PER_ZONE - 1) {
			zone = this->GetZone(IntVector2(zonePos.x + 1, zonePos.y));
			if (zone) zone->chunk.Remesh();
		}


		if (blockInZonePos.y == 0) {
			zone = this->GetZone(IntVector2(zonePos.x, zonePos.y - 1));
			if (zone) zone->chunk.Remesh();
		}
		else if (blockInZonePos.y == cube::BLOCKS_PER_ZONE - 1) {
			zone = this->GetZone(IntVector2(zonePos.x, zonePos.y + 1));
			if (zone) zone->chunk.Remesh();
		}
	}


	
}
cube::Block* cube::World::GetBlock(LongVector3 block_pos) {
	IntVector2 zonePos = cube::Zone::ZoneCoordsFromBlocks(block_pos.x, block_pos.y);
	cube::Zone* zone = this->GetZone(zonePos);
	if (!zone) return nullptr;
	IntVector3 zoneBlockPos(pymod(block_pos.x, cube::BLOCKS_PER_ZONE), pymod(block_pos.y, cube::BLOCKS_PER_ZONE), block_pos.z);

	return zone->GetBlock(zoneBlockPos);
}

cube::Block cube::World::GetBlockInterpolated(LongVector3 block_pos) {
	IntVector2 zonePos = cube::Zone::ZoneCoordsFromBlocks(block_pos.x, block_pos.y);
	cube::Zone* zone = this->GetZone(zonePos);

	if (!zone) {
		cube::Block block;
		block.red = 255;
		block.green = 255;
		block.blue = 255;
		block.field_3 = 0;
		block.type = cube::Block::Air;
		block.breakable = 0;
		return block;
	}
	IntVector3 zoneBlockPos(pymod(block_pos.x, cube::BLOCKS_PER_ZONE), pymod(block_pos.y, cube::BLOCKS_PER_ZONE), block_pos.z);

	return zone->GetBlockInterpolated(zoneBlockPos);
}

cube::Block* cube::World::GetBlock(uint64_t block_x, uint64_t block_y, uint64_t block_z) {
	LongVector3 position(block_x, block_y, block_z);
	return this->GetBlock(position);
}

cube::Block cube::World::GetBlockInterpolated(uint64_t block_x, uint64_t block_y, uint64_t block_z) {
	LongVector3 position(block_x, block_y, block_z);
	return this->GetBlockInterpolated(position);
}

void cube::World::LockZones() {
	EnterCriticalSection(&this->zones_critical_section);
}
void cube::World::UnlockZones() {
	LeaveCriticalSection(&this->zones_critical_section);
}

void cube::World::SetTime(float ms) {
	this->state.time = ms;
}
void cube::World::SetTime(int ms) {
	this->state.time = (float)ms;
}
void cube::World::SetTime(int hour, int minute) {
	this->state.time = (float)((hour * 60 * 60 * 1000) + (minute * 60 * 1000));
}
float cube::World::GetTime() {
	return this->state.time;
}

int SomethingWithAbilityAndHaste(cube::Creature*);
void HandleBinaryToggles(cube::Creature*);

void cube::World::ExecuteAbilityMaybe(cube::Creature* creature)
{
	auto var_B38 = 0x0FFFFFFFFFFFFFFFE;
	if (this->local_creature == creature || (this->field_358 == 0 && creature->entity_data.hostility_type == 0))
	{
		creature->entity_data.binary_toggles &= 0x0FFFB;
		int current_ability = creature->entity_data.current_ability;
		if (current_ability != 0)
		{
			HandleBinaryToggles(creature);
			//Do some math when ability = 133
		}
	}
}

// Todo: Call CW function 0x4F220
int SomethingWithAbilityAndHaste(cube::Creature* creature)
{
	return 0;
}

void HandleBinaryToggles(cube::Creature* creature)
{
	int current_ability = creature->entity_data.current_ability;

	int a1 = current_ability - 95;
	if (a1 & 0xFF <= 57 && (0x200880002000001 >> (a1 & 0xFF)) & 1 == 1)
	{
		return;
	}

	if (current_ability == 159 || (current_ability == 161 && creature->entity_data.hostility_type == 0))
	{
		return;
	}

	int a2 = current_ability - 118;
	if (a2 & 0xFF <= 45 && (0x30C010000CC9 >> (a2 & 0xFF)) & 1 == 1)
	{
		return;
	}

	int a3 = current_ability - 80;
	if (a3 & 0xFF <= 10 && (0x7F7 >> (a3 & 0xFF)) & 1 == 1)
	{
		return;
	}

	if (current_ability == 12)
	{
		return;
	}

	if ((float)(SomethingWithAbilityAndHaste(creature) + 200) <= creature->entity_data.time_since_ability && current_ability == 147)
	{
		return;
	}

	if ((a1 & 0xFF <= 60 && (0x104327400040004F >> (a1 & 0xFF)) & 1 == 1) || current_ability == 35 || creature->entity_data.binary_toggles != 0x2012)
	{
		creature->entity_data.binary_toggles &= 0x0FFBF;
		return;
	}

	creature->entity_data.binary_toggles |= 4;
	return;
}
