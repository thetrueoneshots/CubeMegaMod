#pragma once
#include "../../CubeMod.h"

class CreatureUpdatesMod : public CubeMod
{
public:
	CreatureUpdatesMod() {
		m_Name = "Creature Updates Mod";
		m_FileName = "CreatureUpdatesMod";
		m_ID = 4;
		m_Version = { 1, 1, 0 };
	}

	void Initialize();

	Priority OnCreatureArmorCalculatedPriority = NormalPriority;
	void OnCreatureArmorCalculated(cube::Creature* creature, float* armor);

	Priority OnCreatureCriticalCalculatedPriority = NormalPriority;
	void OnCreatureCriticalCalculated(cube::Creature* creature, float* critical);

	Priority OnCreatureAttackPowerCalculatedPriority = NormalPriority;
	void OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power);

	Priority OnCreatureSpellPowerCalculatedPriority = NormalPriority;
	void OnCreatureSpellPowerCalculated(cube::Creature* creature, float* power);

	Priority OnCreatureHasteCalculatedPriority = NormalPriority;
	void OnCreatureHasteCalculated(cube::Creature* creature, float* haste);

	Priority OnCreatureHPCalculatedPriority = NormalPriority;
	void OnCreatureHPCalculated(cube::Creature* creature, float* hp);

	Priority OnCreatureResistanceCalculatedPriority = NormalPriority;
	void OnCreatureResistanceCalculated(cube::Creature* creature, float* resistance);

	Priority OnCreatureRegenerationCalculatedPriority = NormalPriority;
	void OnCreatureRegenerationCalculated(cube::Creature* creature, float* regeneration);

	Priority OnCreatureManaGenerationCalculatedPriority = NormalPriority;
	void OnCreatureManaGenerationCalculated(cube::Creature* creature, float* manaGeneration);
};