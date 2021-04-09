#include "TempClass2.h"

void TempClass2::GenerateStarterGear(cube::Game* game, cube::Creature* player)
{
}

int TempClass2::GetUltimateAbilityId(cube::Creature* player)
{
	return 95;
}

int TempClass2::GetUltimateAbilityCooldown(cube::Creature* player, int abilityID)
{
	return 3000;
}

bool TempClass2::CanEquipItem(cube::Item* item)
{
	return false;
}
