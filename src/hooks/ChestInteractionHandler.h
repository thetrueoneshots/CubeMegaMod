/*
* Hook for opening the self made chests. Here, the chests are opened, 
* items are added to the player and the gain of the item is announced.
*/

#pragma once
#include "cwsdk.h"

#include "../cwsdk-extension/creature/Creature.h"
#include "../cwsdk-extension/helper/Helper.h"

#include "../CubeMod.h"

int ChestInteractionHandler(cube::Game *game, cube::Creature *creature, int type) {
	for (CubeMod* mod : g_Mods) {
		if (mod->OnChestInteraction(game, creature, type)) {
			return 1;
		}
	}
	return 0;
}

extern "C" void OnChestInteraction(cube::Game* game, cube::Creature* creature) {
	int type = creature->entity_data.race - 181;
	if (!ChestInteractionHandler(game, creature, type))
	{
		return;
	}

	// Check if the chest is visible on the map.
	if (creature->entity_data.binary_toggles >> (int)cube::Enums::StateFlags::VisibleOnMap & 1 == 1)
	{
		creature->entity_data.binary_toggles ^= 1 << (int)cube::Enums::StateFlags::VisibleOnMap;
	}

	// Open the chest
	creature->entity_data.interaction_state = 2;
}

GETTER_VAR(void*, ASMIsChestOpen_jmpback);
GETTER_VAR(void*, ASMIsChestOpen_bail);
__attribute__((naked)) void ASMIsChestOpen() {
	asm(".intel_syntax \n"

		"cmp byte ptr [rdi + 0x19C], 2 \n"
		"jne 1f \n"

		// Todo: If this chrashes, then jmpback should work.
		DEREF_JMP(ASMIsChestOpen_bail)

		"1: \n"

		// Original code
		"mov rax, [rsi + 0x8] \n"
		"mov rcx, [rax + 0x448]\n"
		"mov rax, [rdi + 0x10] \n"
		"mov rdx, [rdi + 0x18] \n"
		"mov r8, [rdi + 0x20]  \n"
		"sub rax, [rcx + 0x10] \n"
		"sub rdx, [rcx + 0x18] \n"
		"sub r8, [rcx + 0x20]  \n"
		
		DEREF_JMP(ASMIsChestOpen_jmpback)

		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMChestInteractionHandler_jmpback);
__attribute__((naked)) void ASMChestInteractionHandler() {
	asm(".intel_syntax \n"
		// No original code is needed.

		PUSH_ALL
		"mov rdx, rdi \n"
		"mov rcx, rsi \n"

		PREPARE_STACK

		"call OnChestInteraction \n"

		RESTORE_STACK

		POP_ALL

		DEREF_JMP(ASMChestInteractionHandler_jmpback)

		".att_syntax \n"
	);
}

void SetupChestInteractionHandler() {
	WriteFarJMP(g_Base + 0x99288, (void*)&ASMChestInteractionHandler);
	ASMChestInteractionHandler_jmpback = (void*)(g_Base + 0x988C1);

	// Todo: Create an OnCreateInteraction(cube::Creature*) function.
	WriteFarJMP(g_Base + 0x991A3, (void*)&ASMIsChestOpen);
	ASMIsChestOpen_jmpback = (void*)(g_Base + 0x991C6);
	ASMIsChestOpen_bail = (void*)(g_Base + 0x99298);
}