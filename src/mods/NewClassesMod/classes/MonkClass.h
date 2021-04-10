#pragma once
#include "../CharacterClass.h"

class MonkClass : public CharacterClass {
public:
	MonkClass() : CharacterClass("Monk", L"Monk") {}
	~MonkClass() {}

	void Initialize(cube::Game* game) override;
	void GenerateStarterGear(cube::Game* game, cube::Creature* player) override;
	int GetUltimateAbilityId(cube::Creature* player) override;
	int GetUltimateAbilityCooldown(cube::Creature* player, int abilityID) override;
	int GetShiftAbilityId(cube::Creature* player) override;
	int GetMiddleMouseAbilityId(cube::Creature* player) override;
	bool CanEquipItem(cube::Item* item) override;
	int ManaGenerationType(cube::Creature* player) override;
};