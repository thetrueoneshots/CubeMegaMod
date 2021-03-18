#include "WorldGenMod.h"

#include "WorldGenOverride/WorldGenOverride.h"

void WorldGenMod::Initialize()
{
	cube::Game::SetRestrictedSpawnRegions(false);
	WorldGenOverrideIntialize();
}