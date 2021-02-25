#include "Game.h"
#include "../cwsdk.h"
#include <thread>

float degrees_to_radians(float degrees) {
	return (degrees * 3.1415926535) / 180.0;
}
float radians_to_degrees(float radians) {
	return (radians * 180.0) / 3.1415926535;
}

cube::Creature* cube::Game::GetPlayer() {
	return this->world->local_creature;
}

bool cube::Game::TraceCrosshairToBlock(float reach_in_blocks_from_camera, bool want_face_block, LongVector3* result, bool pass_through_water) {
	//Calculate the direction the camera is in
	f32 cameraYaw = this->camera_angle.z;
	f32 cameraPitch = this->camera_angle.x;
	f32 yaw = degrees_to_radians(cameraYaw + 90.0);
	f32 pitch = degrees_to_radians(cameraPitch);

	f32 camera_x_direction = cos(yaw) * sin(pitch);
	f32 camera_y_direction = sin(yaw) * sin(pitch);
	f32 camera_z_direction = -cos(pitch);

	//Get the absolute location of the camera, in world units (not blocks)
	i64 camera_x = this->global_camera_position.x;
	i64 camera_y = this->global_camera_position.y;
	i64 camera_z = this->global_camera_position.z;

	//We're going to start the raycast at the current position of the camera.
	i64 blockx = pydiv(camera_x, DOTS_PER_BLOCK);
	i64 blocky = pydiv(camera_y, DOTS_PER_BLOCK);
	i64 blockz = pydiv(camera_z, DOTS_PER_BLOCK);

	//These are for the case that you want the block on the face of whatever it hits.
	i64 lastblockx = blockx;
	i64 lastblocky = blocky;
	i64 lastblockz = blockz;

	f32 reach_limit = (f32)DOTS_PER_BLOCK * reach_in_blocks_from_camera; //maximum reach in world units
	f32 raycast_precision = 1000.0;
	bool withinReach = false;

	//Move the position back in the opposite direction until it hits a block.
	for (f32 world_units_traveled = 0.0; world_units_traveled < reach_limit; world_units_traveled += raycast_precision) {
		//Update previous block before changing the current block
		lastblockx = blockx;
		lastblocky = blocky;
		lastblockz = blockz;
		blockx = pydiv(camera_x, DOTS_PER_BLOCK);
		blocky = pydiv(camera_y, DOTS_PER_BLOCK);
		blockz = pydiv(camera_z, DOTS_PER_BLOCK);
		//Figure out what's in the new location
		cube::Block block = this->world->GetBlockInterpolated(blockx, blocky, blockz);
		bool isAir = block.type == cube::Block::Type::Air;
		bool isWater = block.type == cube::Block::Water;
		bool canPassThrough = isAir || (isWater && pass_through_water);
		if (!canPassThrough) { //If the block is a block we cannot pass through (we hit something)
			withinReach = true;
			if (want_face_block) {
				//If you want the face block, change the block coords to whatever was seen last time. ie, go back one.
				blockx = lastblockx;
				blocky = lastblocky;
				blockz = lastblockz;
			}
			break; //Leave loop if successfully hit a block

		}
		//Move the position back a tiny bit
		camera_x -= (i64)(camera_x_direction * raycast_precision);
		camera_y -= (i64)(camera_y_direction * raycast_precision);
		camera_z -= (i64)(camera_z_direction * raycast_precision);
	}

	LongVector3 position(blockx, blocky, blockz);

	//We've got a block coordinate now, whether it be the block we were looking at, the block on the face of another, or the block at the edge of our reach.
	if (withinReach) {
		result->x = blockx;
		result->y = blocky;
		result->z = blockz;
	}

	return withinReach;
}

void cube::Game::PrintMessage(const wchar_t* message, FloatRGBA* color) {
	this->gui.chat_widget->PrintMessage(message, color);
}
void cube::Game::PrintMessage(const wchar_t* message) {
	this->gui.chat_widget->PrintMessage(message);
}
void cube::Game::PrintMessage(const wchar_t* message, char red, char green, char blue) {
	this->gui.chat_widget->PrintMessage(message, red, green, blue);
}
void cube::Game::PlaySoundEffect(SoundEffect sound_id, LongVector3& position, float volume, float speed, bool unkbool) {
	((void(*)(cube::Game*, u32, LongVector3&, float, float, char))CWOffset(0x0A0420))(this, sound_id, position, volume, speed, unkbool);
}
void cube::Game::PlaySoundEffect(SoundEffect sound_id, float volume, float speed, bool unkbool) {
	this->PlaySoundEffect(sound_id, this->global_camera_position, volume, speed, unkbool);
}

// This never worked properly, but I'll leave it here to demonstrate a little about how remeshing works
/*void cube::Game::RemeshZone(int x, int y) {
	EnterCriticalSection(&world->zones_critical_section);
	cube::Zone* zone = this->world->zones.at(IntVector2(x, y));
	LeaveCriticalSection(&world->zones_critical_section);

	if (zone) {
		EnterCriticalSection(&world->critical_section_2);
		this->renderer->RemeshZone(x, y);

		EnterCriticalSection(&world->zones_critical_section);
		EnterCriticalSection(&world->zones_mesh_critical_section);



		
		std::list<gfx::ChunkBuffer*> old_chunkbuffers;

		for (gfx::ChunkBuffer* chunkbuffer : zone->chunk.chunkbuffers) {
			old_chunkbuffers.push_back(chunkbuffer);
		}

		if (zone->chunk.new_chunkbuffers.size() > 1) {
			zone->chunk.chunkbuffers.clear();
		}


		for (gfx::ChunkBuffer* new_chunkbuffer : zone->chunk.new_chunkbuffers) {
			zone->chunk.chunkbuffers.push_back(new_chunkbuffer);
		}

		zone->chunk.new_chunkbuffers.clear();

		LeaveCriticalSection(&world->zones_mesh_critical_section);
		LeaveCriticalSection(&world->zones_critical_section);
		LeaveCriticalSection(&world->critical_section_2);
	}
}

void cube::Game::QueueZoneRemesh(int x, int y) {
	EnterCriticalSection(&world->zones_critical_section);
	cube::Zone* zone = this->world->zones.at(IntVector2(x, y));
	if (zone) zone->chunk.Remesh();
	LeaveCriticalSection(&world->zones_critical_section);

	std::thread( &cube::Game::RemeshZone, this, x, y ).detach();
}*/