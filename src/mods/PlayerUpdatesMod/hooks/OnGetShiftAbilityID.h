/*
* Hook for modifying the ultimate ability ID.
*/
#pragma once

#include "cwsdk.h"
#include "../../../cwsdk-extension.h"
#include "../PlayerUpdatesMod.h"
#include <stddef.h>

enum ControlIndex : int
{
	button_attack = 0,
	button_special_attack,
	button_class_skill,
	button_ultimate_skill,
	button_quick_item,
	button_up,
	button_down,
	button_left,
	button_right,
	button_jump,
	button_dodge,
	button_use,
	button_lamp,
	button_walk,
	button_call_pet,
	button_world_map,
	button_ring_menu,
	button_inventory,
	button_crafting_menu,
	button_system_menu,
	button_multiplayer_menu,
	button_zoom_in,
	button_zoom_out
	//Left_Shift = 0x2,
	//MiddleMouse = 0xA
};

extern "C" int OnShiftAbilityID(cube::Game* game, cube::Creature* player) {
	if (player->entity_data.classType <= 4)
	{
		return 0;
	}

	if (player->entity_data.hostility_type != (int)cube::Enums::EntityBehaviour::Player)
	{
		return 0;
	}

	int index = player->entity_data.classType - 5;
	if (index < 0 || index >= MOD->m_Classes.size())
	{
		return 0;
	}

	if (game->control_states[ControlIndex::button_class_skill])
	{
		player->entity_data.current_ability = MOD->m_Classes.at(index)->GetShiftAbilityId(player);
	}

	if (game->control_states[ControlIndex::button_dodge])
	{
		int ability = MOD->m_Classes.at(index)->GetMiddleMouseAbilityId(player);
		player->entity_data.current_ability = ability;
		if (ability > 0)
		{
			player->entity_data.time_since_ability = 0.f;
			game->control_states[ControlIndex::button_dodge] = false;
		}
	}
	return 0;
}

GETTER_VAR(void*, ASMOnGetShiftAbilityID_jmpback);
GETTER_VAR(void*, ASMOnGetShiftAbilityID_jmpback_2);
__attribute__((naked)) void ASMOnGetShiftAbilityID() {
	asm(".intel_syntax \n"

		// old code
		"mov rax, [r13 + 8] \n"
		"mov rcx, [rax + 0x448] \n"

		PUSH_ALL
		"mov rdx, rcx \n"
		"mov rcx, r13 \n"
		PREPARE_STACK
		"call OnShiftAbilityID \n"
		RESTORE_STACK
		POP_ALL
		// old code
		"cmp byte ptr [rcx + 0x14C], 4 \n"
		"jne 1f \n"
		DEREF_JMP(ASMOnGetShiftAbilityID_jmpback)

		"1: \n"
		DEREF_JMP(ASMOnGetShiftAbilityID_jmpback_2)

		".att_syntax \n"
	);
}

void InitializeOnGetShiftIDHandler()
{
	WriteFarJMP(CWOffset(0x8F223), (void*)&ASMOnGetShiftAbilityID);
	ASMOnGetShiftAbilityID_jmpback = CWOffset(0x8F237);
	ASMOnGetShiftAbilityID_jmpback_2 = CWOffset(0x8F240);
}