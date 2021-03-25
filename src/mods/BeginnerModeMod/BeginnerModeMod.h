#pragma once
#include "../../CubeMod.h"

class BeginnerModeMod : public CubeMod
{
public:
	BeginnerModeMod() {
		m_Name = "Beginner Mode Mod";
		m_FileName = "BeginnerModeMod";
		m_ID = 7;
		m_Version = { 1, 0, 0 };
	}

	Priority OnCreatureArmorCalculatedPriority = NormalPriority;
	void OnCreatureArmorCalculated(cube::Creature* creature, float* armor);

	Priority OnCreatureAttackPowerCalculatedPriority = NormalPriority;
	void OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power);

	Priority OnCreatureSpellPowerCalculatedPriority = NormalPriority;
	void OnCreatureSpellPowerCalculated(cube::Creature* creature, float* power);

	Priority OnCreatureHPCalculatedPriority = NormalPriority;
	void OnCreatureHPCalculated(cube::Creature* creature, float* hp);

	Priority OnCreatureResistanceCalculatedPriority = NormalPriority;
	void OnCreatureResistanceCalculated(cube::Creature* creature, float* resistance);
};