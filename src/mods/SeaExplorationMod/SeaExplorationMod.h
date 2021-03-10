#pragma once
#include "../../CubeMod.h"

#include "event/DivingEvent.h"

class SeaExplorationMod : public CubeMod
{
private:
	cube::DivingEvent* m_DivingEvent;
public:
	SeaExplorationMod() {
		m_Name = "Sea Exploration Mod";
		m_ID = 1;
		m_Version = { 1, 0, 0 };
	}

	int OnChestInteraction(cube::Game* game, cube::Creature* creature, int type);
	void OnGameTick(cube::Game* game);
	void Initialize();
};