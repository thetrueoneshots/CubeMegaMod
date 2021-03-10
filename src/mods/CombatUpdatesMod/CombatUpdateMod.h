#pragma once
#include "../../CubeMod.h"

struct CombatUpdateData
{
	bool doubleTap;
};

class CombatUpdateMod : public CubeMod
{
private:
	CombatUpdateData m_Data;
public:
	CombatUpdateMod() {
		m_Name = "Combat Update Mod";
		m_FileName = "CombatUpdateMod";
		m_ID = 3;
		m_Version = { 1, 0, 0 };
		m_Data = { true };
		Load(&m_Data, sizeof(m_Data));
	}

	void OnGetKeyboardState(BYTE* diKeys);
	int OnChat(std::wstring* message);
private:
	bool CheckMovementButtonPress(cube::DButton* button, cube::DButton* lCntr);
};