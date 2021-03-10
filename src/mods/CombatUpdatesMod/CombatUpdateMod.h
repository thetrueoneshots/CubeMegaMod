#pragma once
#include "../../CubeMod.h"

class CombatUpdateMod : public CubeMod
{
public:
	CombatUpdateMod() {
		m_Name = "Combat Update Mod";
		m_ID = 3;
		m_Version = { 1, 0, 0 };
	}

	void OnGetKeyboardState(BYTE* diKeys);
private:
	bool CheckMovementButtonPress(cube::DButton* button, cube::DButton* lCntr);
};