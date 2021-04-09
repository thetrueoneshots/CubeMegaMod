#pragma once
#include "../CharacterClass.h"

class TempClass1 : public CharacterClass {
public:
	TempClass1() : CharacterClass("Ravager", L"Ravager") {}
	~TempClass1() {}

	void GenerateStarterGear(cube::Game* game, cube::Creature* player) override;
	int GetUltimateAbilityId(cube::Creature* player) override;
	int GetUltimateAbilityCooldown(cube::Creature* player, int abilityID) override;
	bool CanEquipItem(cube::Item* item) override;
};