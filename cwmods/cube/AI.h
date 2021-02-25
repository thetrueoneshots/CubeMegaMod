#ifndef CUBE_AI_H
#define CUBE_AI_H

#include "../IDA/types.h"
#include <list>
#include <map>
#include "../common/Vector3.h"

namespace cube {
class AI {
    public:
		float field_0;
		int32_t some_time_ms;
		int32_t field_8;
		uint8_t unk_bool_0;
		uint8_t unk_bool_1;
		char field_E;
		char field_F;
		__int64 field_10;
		int64_t field_18;
		int32_t field_20;
		FloatVector3 unk_vec3_float;
		FloatVector3 camera_looking_at_block_offset;
		int32_t field_3C;
		int32_t field_40;
		uint8_t field_44;
		uint8_t field_45;
		uint8_t field_46;
		uint8_t in_spiritworld;
		int32_t field_48;
		int32_t field_4C;
		std::list<void*> unk_list_0x50_node_size_0xD8;
		int32_t physics_flags;
		int32_t binary_toggles;
		LongVector3 position;
		float graphical_size;
		float hitbox_size;
		float physical_size;
		int32_t field_8C;
		int64_t field_90;
		std::map<void*, void*> unk_map_0x98_node_size_0x40;
		std::map<void*, void*> unk_map_0xA8_node_size_0x28;
		int64_t field_B8;
		int32_t field_C0;
		int32_t field_C4;
		int64_t field_C8;
		int64_t field_D0;
		int64_t field_D8;
		LongVector3 some_position;
		int64_t field_F8;
		int64_t field_100;
		int64_t field_108;
		std::list<void*> unk_list_0x110_node_size_0x20;
		std::map<void*, void*> unk_map_0x120_node_size_0x28;
		std::list<void*> unk_list_0x130_node_size_0x20;
		int64_t field_140;
		int64_t field_148;
    };
}

static_assert(sizeof(cube::AI) == 0x150, "cube::AI is not the correct size.");

#endif // ZONE_H
