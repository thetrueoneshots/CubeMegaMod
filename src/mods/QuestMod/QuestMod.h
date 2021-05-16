#pragma once
#include "../../CubeMod.h"
#include "../../hooks.h"
#include "../../memory_helper/memory_helper.h"

class QuestMod : public CubeMod
{
private:
	std::list<long long> m_TalkedIds;
public:
	QuestMod() {
		m_Name = "Quest Mod";
		m_FileName = "QuestMod";
		m_ID = 10;
		m_Version = { 1, 2, 0 };
	}

	void OnGameTick(cube::Game* game);
	void Initialize();
	void OnCreatureDeath(cube::Creature* creature, cube::Creature* attacker);
	int OnCreatureTalk(cube::Game* game, cube::Creature* creature);
};