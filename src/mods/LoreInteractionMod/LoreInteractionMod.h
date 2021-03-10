#pragma once
#include "../../CubeMod.h"

class LoreInteractionMod : public CubeMod
{
public:
	LoreInteractionMod() {
		m_Name = "Lore Interaction Mod";
		m_ID = 2;
		m_Version = { 1, 0, 0 };
	}

	void OnLoreIncrease(cube::Game* game, int value);
};