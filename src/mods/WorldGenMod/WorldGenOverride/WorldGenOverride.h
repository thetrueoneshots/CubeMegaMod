/*
* Hook for overwriting the world gen, by modifying the getbiome type function.
*/

#pragma once

#include "../Noise/SimplexNoise.h"
#include "cwsdk.h"
#include "../src/hooks.h"
#include <math.h> 

const static float SCL = 1.f;

int DistanceSquared(IntVector2 p1, IntVector2 p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;
	return dx * dx + dy * dy;
}

int GetBiomeType(int x, int y)
{
	int dx = std::floor(x / 7);
	int dy = std::floor(y / 7);

	int seed = SimplexNoise::noise(dx, dy) * INT_MAX;
	std::srand(seed);
	return std::rand() % 6;
}

int GetHeight(int x, int y)
{
	const static float MULT = std::sqrt(3 * 3 + 3 * 3);
	int dx = std::abs((x % 7) - 3);
	int dy = std::abs((y % 7) - 3);
	double dist = std::sqrt(DistanceSquared(IntVector2(dx, dy), IntVector2(0, 0)));
	double multiplier = (MULT - dist) / MULT;
	double height = multiplier * (2.f + SimplexNoise::noise(x * SCL, y * SCL)) / 3.f;
	if (height > 0.5f)
	{
		return 2;
	}
	else if (height > 0.25f)
	{
		return 1;
	}
	return 0;
}

extern "C" int GetRegionType(int x, int y) {
	static const int REGION_TYPES[6][2] = {
		{2, 7},
		{8, 4},
		{10, 3},
		{11, 6},
		{9, 13},
		{12, 5},
	};

	if (GetHeight(x, y) == 0)
	{
		return 1;
	}

	return REGION_TYPES[GetBiomeType(x, y)][GetHeight(x, y) - 1];
}

__attribute__((naked)) void ASMUpdateGetBiomeType() {
	asm(".intel_syntax \n"

		"push r15 \n"

		PUSH_ALL

		"mov rcx, rdx \n"
		"mov rdx, r8 \n"

		PREPARE_STACK

		"call GetRegionType \n"

		RESTORE_STACK

		"mov [rsp], rax \n"

		POP_ALL

		"mov rax, r15 \n"
		"pop r15 \n"

		"ret \n"

		".att_syntax \n"
	);
}

void WorldGenOverrideIntialize()
{
	WriteFarJMP(CWOffset(0x2B909A), (void*)&ASMUpdateGetBiomeType);
}