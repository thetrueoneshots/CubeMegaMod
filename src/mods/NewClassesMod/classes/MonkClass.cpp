#include "MonkClass.h"

void Popup(const char* title, const char* msg) {
	MessageBoxA(0, msg, title, MB_OK | MB_ICONINFORMATION);
}

void MonkClass::GenerateStarterGear(cube::Game* game, cube::Creature* player)
{
	cube::Item chest(4, 0);
	chest.rarity = 1;
	chest.region = player->entity_data.current_region;

	player->entity_data.equipment.creature = chest;
}

int MonkClass::GetUltimateAbilityId(cube::Creature* player)
{
	return 148;
}

int MonkClass::GetUltimateAbilityCooldown(cube::Creature* player, int abilityID)
{
	return 5000;
}

int MonkClass::GetShiftAbilityId(cube::Creature* player)
{
	return 146;
}

int MonkClass::GetMiddleMouseAbilityId(cube::Creature* player)
{
	if (player->entity_data.current_ability == 50)
	{
		if (player->stamina >= 0.1f) {
			player->stamina += 0.24f;
			return 50;
		}
		return 0;
	}

	if (player->stamina >= 0.5f)
	{
		return 50;
	}
	return 0;
}

bool MonkClass::CanEquipItem(cube::Item* item)
{
	if (item->category == 3)
	{
		return false;
	}
	return true;
}
