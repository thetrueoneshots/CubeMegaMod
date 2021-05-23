/*
* Hook for overwriting the world gen, by modifying the getbiome type function.
*/
#pragma once

#include "../Noise/SimplexNoise.h"
#include "cwsdk.h"
#include <math.h> 
#include <assert.h>

enum BuildingTypes : int
{
	SavannaTree = 1,
	PineTree = 2,
	BasicTree = 3,
	JungleTree = 4,
	PalmTree = 5,
	ShrineOfLife = 53,
	WhiteBuildingRoofHigh = 43,
	GrayBuildingRoofHigh = 96,
	BuildingWithFirePlace = 88,
	DungeonBuildingWoodWalls = 77,
	DungeonBuoldingWoodRoom = 78,
};

struct UnkStruct
{
};

/*int DistanceSquared(IntVector2 p1, IntVector2 p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;
	return dx * dx + dy * dy;
}*/

/*int GetBiomeType(int x, int y)
{
	int dx = std::floor(x / 7.f);
	int dy = std::floor(y / 7.f);

	return std::round(SimplexNoise::noise(dx, dy) * 5.f);
}*/

/*int GetHeight(int x, int y)
{
	const static float MULT = std::sqrt(3 * 3 + 3 * 3);
	int dx = std::abs((std::abs(x) % 7) - 3);
	int dy = std::abs((std::abs(y) % 7) - 3);
	double dist = std::sqrt(DistanceSquared(IntVector2(dx, dy), IntVector2(0, 0)));
	double multiplier = (MULT - dist) / MULT;
	double height = multiplier * (2.f + SimplexNoise::noise(x, y)) / 3.f;

	if (height > 0.5f)
	{
		return 2;
	}
	else if (height > 0.25f)
	{
		return 1;
	}
	return 0;
}*/

extern "C" int GetBuildingType(cube::World* world, int x, int y, IntVector2* intVector2) {
	int ARR[] = {
		22,
		23,
		24,
		24,
		25,
		53,
		0,
		35,
		36,
		37,
		40,
		43,
		77,
	};

	int size = sizeof(ARR) / sizeof(*ARR);
	int res = ((int)((SimplexNoise::noise(x, y) + 1.f) * size)) % size;
	return ARR[res];
}

__attribute__((naked)) void ASMBuildingTypeOverride() {
	asm(".intel_syntax \n"

		"sub rsp, 0x110 \n"
		"movups xmmword ptr [rsp + 0x10], xmm0 \n"
		"movups xmmword ptr [rsp + 0x20], xmm1 \n"
		"movups xmmword ptr [rsp + 0x30], xmm2 \n"
		"movups xmmword ptr [rsp + 0x40], xmm3 \n"
		"movups xmmword ptr [rsp + 0x50], xmm4 \n"
		"movups xmmword ptr [rsp + 0x60], xmm5 \n"
		"movups xmmword ptr [rsp + 0x70], xmm6 \n"
		"movups xmmword ptr [rsp + 0x80], xmm7 \n"
		"movups xmmword ptr [rsp + 0x90], xmm8 \n"
		"movups xmmword ptr [rsp + 0xA0], xmm9 \n"
		"movups xmmword ptr [rsp + 0xB0], xmm10 \n"
		"movups xmmword ptr [rsp + 0xC0], xmm11 \n"
		"movups xmmword ptr [rsp + 0xD0], xmm12 \n"
		"movups xmmword ptr [rsp + 0xE0], xmm13 \n"
		"movups xmmword ptr [rsp + 0xF0], xmm14 \n"
		"movups xmmword ptr [rsp + 0x100], xmm15 \n"

		PREPARE_STACK
		"call GetBuildingType \n"
		RESTORE_STACK

		"movups xmm0, xmmword ptr [rsp + 0x10] \n"
		"movups xmm1, xmmword ptr [rsp + 0x20] \n"
		"movups xmm2, xmmword ptr [rsp + 0x30] \n"
		"movups xmm3, xmmword ptr [rsp + 0x40] \n"
		"movups xmm4, xmmword ptr [rsp + 0x50] \n"
		"movups xmm5, xmmword ptr [rsp + 0x60] \n"
		"movups xmm6, xmmword ptr [rsp + 0x70] \n"
		"movups xmm7, xmmword ptr [rsp + 0x80] \n"
		"movups xmm8, xmmword ptr [rsp + 0x90] \n"
		"movups xmm9, xmmword ptr [rsp + 0xA0] \n"
		"movups xmm10, xmmword ptr [rsp + 0xB0] \n"
		"movups xmm11, xmmword ptr [rsp + 0xC0] \n"
		"movups xmm12, xmmword ptr [rsp + 0xD0] \n"
		"movups xmm13, xmmword ptr [rsp + 0xE0] \n"
		"movups xmm14, xmmword ptr [rsp + 0xF0] \n"
		"movups xmm15, xmmword ptr [rsp + 0x100] \n"

		"add rsp, 0x110 \n"

		"ret \n"

		".att_syntax \n"
	);
}

void BuildingTypeOverrideIntialize()
{
	WriteFarJMP(CWOffset(0x2D53D0), (void*)&ASMBuildingTypeOverride);
}