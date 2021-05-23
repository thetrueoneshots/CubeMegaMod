/*
* Hook for overwriting the world gen, by modifying the getbiome type function.
*/

#pragma once

#include "../Noise/SimplexNoise.h"
#include "cwsdk.h"
#include <math.h> 

int DistanceSquared(IntVector2 p1, IntVector2 p2)
{
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;
	return dx * dx + dy * dy;
}

int GetBiomeType(int x, int y)
{
	int dx = std::floor(x / 7.f);
	int dy = std::floor(y / 7.f);

	return std::round(SimplexNoise::noise(dx, dy) * 5.f);
}

int GetHeight(int x, int y)
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
}

extern "C" int GetRegionType(int x, int y) {
	using namespace cube;
	static const int REGION_TYPES[6][2] = {
		{(int)Zone::RegionType::Hills, (int)Zone::RegionType::Mountains},
		{(int)Zone::RegionType::Wetlands, (int)Zone::RegionType::Jungle},
		{(int)Zone::RegionType::Savannah, (int)Zone::RegionType::Woodlands},
		{(int)Zone::RegionType::Snowlands, (int)Zone::RegionType::SnowForest},
		{(int)Zone::RegionType::Desert, (int)Zone::RegionType::Firelands},
		{(int)Zone::RegionType::Deadlands, (int)Zone::RegionType::Darkwoods},
	};

	if (GetHeight(x, y) == 0)
	{
		return (int)Zone::RegionType::Ocean;
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