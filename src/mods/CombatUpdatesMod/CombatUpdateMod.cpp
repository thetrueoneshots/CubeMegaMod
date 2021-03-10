#include "CombatUpdateMod.h"

bool CombatUpdateMod::CheckMovementButtonPress(cube::DButton* button, cube::DButton* lCntr)
{
	if (button->Pressed() == cube::DButton::State::DoubleTap && false) // settings.m_DoubleTapActivated)
	{
		return true;
	}

	if (!false/*settings.m_DoubleTapActivated*/ && button->Pressed() != cube::DButton::State::None && lCntr->Pressed() == cube::DButton::State::Held)
	{
		return true;
	}

	return false;
}

void CombatUpdateMod::OnGetKeyboardState(BYTE* diKeys)
{
	static cube::DButton KeyW(17); //W
	static cube::DButton KeyA(30); //A
	static cube::DButton KeyS(31); //S
	static cube::DButton KeyD(32); //D

	static cube::DButton KeyLCntrl(29); //LCntrl // Todo: Debug

	static cube::DButton Key1(2); //1
	static cube::DButton Key2(3); //2

	if (cube::Helper::InGUI(cube::GetGame()))
	{
		return;
	}

	KeyW.Update(diKeys);
	KeyA.Update(diKeys);
	KeyS.Update(diKeys);
	KeyD.Update(diKeys);

	KeyLCntrl.Update(diKeys);

	Key1.Update(diKeys);
	Key2.Update(diKeys);

	cube::Creature* player = cube::GetGame()->GetPlayer();

	if (Key1.Pressed() == cube::DButton::State::Pressed)
	{
		cube::ConvertMTSAbility().Execute(player);
	}
	if (Key2.Pressed() == cube::DButton::State::Pressed)
	{
		cube::HealAbility().Execute(player);
	}

	if (CheckMovementButtonPress(&KeyW, &KeyLCntrl))
	{
		cube::FarJumpAbility(0).Execute(player);
	}

	if (CheckMovementButtonPress(&KeyA, &KeyLCntrl))
	{
		cube::FarJumpAbility(1).Execute(player);
	}

	if (CheckMovementButtonPress(&KeyS, &KeyLCntrl))
	{
		cube::FarJumpAbility(3).Execute(player);
	}

	if (CheckMovementButtonPress(&KeyD, &KeyLCntrl))
	{
		cube::FarJumpAbility(2).Execute(player);
	}
}
