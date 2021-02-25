#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "Database.h"
#include <windows.h>
#include "../IDA/types.h"
#include <list>
#include <map>
#include <unordered_map>
#include "SpriteManager.h"
#include "ServerUpdates.h"
#include "../common/Vector2.h"
#include "../common/Vector3.h"
#include "Block.h"
#include "Projectile.h"

namespace cube {
	class Creature;
	class Zone;

	class World {
		public:
			class WorldState {
				public:
					int day;
					float time;
					std::map<void*, void*> some_map_size_0x88; // zone states.
					std::map<void*, void*> some_map_size_0x28; // dead creatures.
					std::map<void*, void*> some_map_size_0x28_1; // dropped rewards.
					//std::map<LongVector3, cube::ItemStack*> some_map_size_0x28_1; // dropped rewards.
					// Size of a map is the size of the key + the size of the value. In this case I think the 
					// Key might be an 8 bytes, leaving 4 times 8 bytes for the the value.
					// Value in this case might be 3*8 bytes for the position and 8 bytes for a pointer to the itemstack dropped.
			};

			class AIManager
			{
				public:
					World* world;
					std::map<void*, void*> AIs;
			};

			class UnkVectors {
				public:
					cube::World* world;
					std::vector<void*> unk_vec_0;
					std::vector<void*> unk_vec_1;
					std::vector<void*> unk_vec_2;
			};

			virtual ~World();

			cube::World::WorldState state;
			std::list<cube::Creature*> creatures;
			std::list<void*> unk_list_size_0x18;
			std::list<Projectile> projectiles;
			cube::SpriteManager* spritemanager;
			cube::World::AIManager AI_manager;
			cube::ServerUpdates server_updates;
			std::map<void*, void*> unk_map_0x190;
			std::map<void*, void*> unk_map_0x1A0;
			cube::World::UnkVectors unk_vectors;
			std::string world_name;
			int seed;
			int seeded_rand_buf_0[4];
			int seeded_rand_buf_1[4];
			int seeded_rand_2[1];
			int seeded_rand_buf_3[20];
			int seeded_rand_buf_4[2];
			int seeded_rand_buf_5[2];
			int seeded_rand_buf_6[2];
			int seeded_rand_buf_7[2];
			int seeded_rand_buf_8[8];
			int seeded_rand_buf_9[6];
			int seeded_rand_buf_10[6];
			int seeded_rand_buf_11[10];
			int seeded_rand_buf_12[4];
			int seeded_rand_buf_13[2];
			int seeded_rand_buf_14[2];
			int seeded_rand_buf_15[2];
			__int64 field_358;
			std::vector<void*> unk_vec_0x360;
			std::map<void*, void*> unk_map_0x378;
			std::vector<void*> field_388;
			std::vector<void*> field_3A0;
			cube::Database world_db_database;
			CRITICAL_SECTION zones_mesh_critical_section;
			CRITICAL_SECTION zones_critical_section;
			CRITICAL_SECTION critical_section_2;
			__int64 field_440;
			cube::Creature* local_creature;
			std::map<uint64_t, cube::Creature*> id_to_creature_map;
			std::unordered_map<IntVector2, cube::Zone*> zones;
			std::vector<void*> field_4A0;
			std::vector<void*> field_4B8;
			std::vector<void*> field_4D0;
			std::vector<void*> field_4E8;
			std::vector<void*> field_500;
			std::vector<void*> field_518;
			std::vector<void*> field_530;


			// Methods
			cube::Zone* GetZone(IntVector2 position);
			cube::Zone* GetZone(int x, int y);
			void SetBlock(LongVector3 block_pos, Block block, bool update=true);
			cube::Block* GetBlock(LongVector3 block_pos);
			cube::Block* GetBlock(uint64_t block_x, uint64_t block_y, uint64_t block_z);
			cube::Block GetBlockInterpolated(uint64_t block_x, uint64_t block_y, uint64_t block_z);
			cube::Block GetBlockInterpolated(LongVector3 block_pos);
			void LockZones();
			void UnlockZones();
			void SetTime(float ms);
			void SetTime(int ms);
			void SetTime(int hour, int minute);
			float GetTime();
	};
}

static_assert(sizeof(cube::World) == 0x548, "cube::World is not the correct size.");

#endif // WORLD_H
