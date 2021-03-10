#pragma once
#include "../../CubeMod.h"

#include "event/DivingEvent.h"

struct SeaExplorationData
{
	bool autoGoldUsage;
};

class SeaExplorationMod : public CubeMod
{
private:
	SeaExplorationData m_Data;
	cube::DivingEvent* m_DivingEvent;

public:
	SeaExplorationMod() {
		m_Name = "Sea Exploration Mod";
		m_FileName = "SeaExplorationMod";
		m_ID = 1;
		m_Version = { 1, 0, 0 };

		m_Data = { true };
		Load(&m_Data, sizeof(m_Data));
	}

	int OnChestInteraction(cube::Game* game, cube::Creature* creature, int type);
	void OnGameTick(cube::Game* game);
	int OnChat(std::wstring* message);
	void Initialize();
};