#pragma once
#include "../CharacterClass.h"

class TempClass2 : public CharacterClass {
public:
	TempClass2() : CharacterClass("Summoner", L"Summoner") {}
	~TempClass2() {}

	void GenerateStarterGear(cube::Game* game, cube::Creature* player) override;
	int GetUltimateAbilityId(cube::Creature* player) override;
	int GetUltimateAbilityCooldown(cube::Creature* player, int abilityID) override;
	bool CanEquipItem(cube::Item* item) override;
};