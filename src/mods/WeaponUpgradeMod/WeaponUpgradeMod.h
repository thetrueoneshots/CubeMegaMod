#pragma once
#include "../../CubeMod.h"
#include "../../hooks.h"

class WeaponUpgradeMod : public CubeMod
{
public:
	WeaponUpgradeMod() {
		m_Name = "Weapon Upgrade Mod";
		m_FileName = "WeaponUpgradeMod";
		m_ID = 9;
		m_Version = { 1, 0, 0 };
	}

	void Initialize();
};