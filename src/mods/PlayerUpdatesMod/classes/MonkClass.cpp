#include "MonkClass.h"

void Popup(const char* title, const char* msg) {
	MessageBoxA(0, msg, title, MB_OK | MB_ICONINFORMATION);
}

void MonkClass::Initialize(cube::Game* game, int id)
{
	this->m_Id = id;

	std::wstring w1(L"RulerChieftainMale");
	game->speech.specialization_type_id_map.insert_or_assign(std::make_pair<uint32_t, uint32_t>(m_Id, 0), w1);

	std::wstring w2(L"RulerSorcerer");
	game->speech.specialization_type_id_map.insert_or_assign(std::make_pair<uint32_t, uint32_t>(m_Id, 1), w2);
}

void MonkClass::GenerateStarterGear(cube::Game* game, cube::Creature* player)
{
	cube::Item chest(4, 0);
	chest.rarity = 1;
	chest.region = player->entity_data.current_region;

	player->entity_data.equipment.chest = chest;

	cube::Item fist(3, 4);
	chest.rarity = 0;
	chest.region = player->entity_data.current_region;

	player->entity_data.equipment.weapon_left = fist;
	player->entity_data.equipment.weapon_right = fist;
}

int MonkClass::GetUltimateAbilityId(cube::Creature* player)
{
	if (player->entity_data.specialization == 1)
	{
		return Ability::PuddleHeal;
	}

	return Ability::FullHeal;
}

int MonkClass::GetUltimateAbilityCooldown(cube::Creature* player, int abilityID)
{
	if (player->entity_data.specialization == 1)
	{
		return 30000;
	}

	return 20000;
}

int MonkClass::GetShiftAbilityId(cube::Creature* player)
{
	if (player->entity_data.specialization == 1)
	{
		if (player->entity_data.current_ability == 53)
		{
			return 53;
		}

		if (player->entity_data.time_since_ability <= 250.f)
		{
			return player->entity_data.current_ability;
		}

		return Ability::PuddleLava;
	}

	return 146;
}

int MonkClass::GetMiddleMouseAbilityId(cube::Creature* player)
{
	if (player->entity_data.specialization == 1)
	{
		if (player->entity_data.current_ability == 53)
		{
			return 53;
		}

		if (player->entity_data.time_since_ability <= 250.f)
		{
			return player->entity_data.current_ability;
		}

		return Ability::PuddlePoison;
	}

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
		if (item->id == 4)
		{
			return true;
		}
		return false;
	}
	return true;
}

int MonkClass::ManaGenerationType(cube::Creature* player)
{
	if (player->entity_data.specialization == 1)
	{
		return ManaGenerationType::PassiveManaGain;
	}
	return ManaGenerationType::PassiveManaGain;
}
