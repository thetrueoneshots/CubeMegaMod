#pragma once
#include "../../CubeMod.h"

class GemTraderMod : public CubeMod
{
public:
	GemTraderMod() {
		m_Name = "Gem Trader Mod";
		m_FileName = "GemTraderMod";
		m_ID = 5;
		m_Version = { 1, 0, 0 };
	}

	int OnShopInteraction(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, int classType, long long id);
};