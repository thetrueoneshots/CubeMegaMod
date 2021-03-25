#pragma once
#include "../../CubeMod.h"
#include "../../hooks.h"

class WorldGenMod : public CubeMod
{
public:
	WorldGenMod() {
		m_Name = "World Gen Mod";
		m_FileName = "WorldGenMod";
		m_ID = 6;
		m_Version = { 1, 0, 0 };
	}

	void Initialize();
};