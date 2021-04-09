#include "TempClass.h"

void TempClass1::GenerateStarterGear(cube::Game* game, cube::Creature* player)
{
	return;
}

int TempClass1::GetUltimateAbilityId(cube::Creature* player)
{
	return 148;
}

int TempClass1::GetUltimateAbilityCooldown(cube::Creature* player, int abilityID)
{
	return 20000;
}

bool TempClass1::CanEquipItem(cube::Item* item)
{
	return true;
}
