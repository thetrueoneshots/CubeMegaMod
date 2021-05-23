#include "WorldGenMod.h"

#include "WorldGenOverride/BiomeTypeOverwrite.h"
#include "WorldGenOverride/BuildingTypeOverwrite.h"

void WorldGenMod::Initialize()
{
	cube::Game::SetRestrictedSpawnRegions(false);
	WorldGenOverrideIntialize();
	BuildingTypeOverrideIntialize();
}