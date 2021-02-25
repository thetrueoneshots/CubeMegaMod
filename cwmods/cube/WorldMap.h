#ifndef WORLDMAP_H
#define WORLDMAP_H

#include "../IDA/types.h"
#include <windows.h>
#include "World.h"
#include "../common/Vector3.h"
#include "../plasma/D3D11Engine.h"

namespace cube {
class WorldMap {
    public:
		virtual ~WorldMap();

		cube::World* world;
		plasma::D3D11Engine* d3d11engine;
		__int64 field_18;
		__int64 field_20;
		__int64 field_28;
		__int64 field_30;
		__int64 field_38;
		__int64 field_40;
		__int64 field_48;
		__int64 field_50;
		FloatVector3 rotation;
		int field_64;
		__int64 field_68;
		__int64 field_70;
		__int64 field_78;
		__int64 field_80;
		__int64 field_88;
		__int64 field_90;
		__int64 field_98;
		__int64 field_A0;
		__int64 field_A8;
		__int64 field_B0;
		__int64 field_B8;
		__int64 field_C0;
		int field_C8;
		_BYTE gapCC[52];
		LongVector3 cursor_position;
		__int64 field_118;
		__int64 field_120;
		__int64 field_128;
		__int64 field_130;
		__int64 field_138;
		__int64 field_140;
		__int64 field_148;
		int field_150;
		int field_154;
		int field_158;
		int field_15C;
		int field_160;
		char flightmaster_mode;
		char field_165;
		char field_166;
		char field_167;
		char field_168;
		char field_169;
		char field_16A;
		char field_16B;
		char field_16C;
		char field_16D;
		char field_16E;
		char field_16F;
		__int64 field_170;
		__int64 field_178;
		__int64 field_180;
		__int64 field_188;
		__int64 field_190;
		__int64 field_198;
		CRITICAL_SECTION critical_section_0;
		CRITICAL_SECTION critical_section_1;
    };
}

static_assert(sizeof(cube::WorldMap) == 0x1F0, "cube::WorldMap is not the correct size.");

#endif // WORLDMAP_H
