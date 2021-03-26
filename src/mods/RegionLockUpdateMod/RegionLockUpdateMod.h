#pragma once
#include "../../CubeMod.h"

class RegionLockUpdateMod : public CubeMod
{
public:
	RegionLockUpdateMod() {
		m_Name = "Region Lock Update Mod";
		m_FileName = "RegionLockUpdateMod";
		m_ID = 8;
		m_Version = { 1, 0, 0 };
	}

	void Initialize();
};