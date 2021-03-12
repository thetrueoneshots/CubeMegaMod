#pragma once
#include "../../CubeMod.h"

class ShopUpdateMod : public CubeMod
{
public:
	ShopUpdateMod() {
		m_Name = "Shop Update Mod";
		m_FileName = "ShopUpdateMod";
		m_ID = 5;
		m_Version = { 1, 0, 0 };
	}

	int OnShopInteraction(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, int classType, long long id);
};