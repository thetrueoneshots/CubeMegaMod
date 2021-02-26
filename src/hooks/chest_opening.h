/*
* Hook for opening the self made chests. Here, the chests are opened, 
* items are added to the player and the gain of the item is announced.
*/

#pragma once
#include "cwsdk.h"

#include "../cwsdk-extension/creature/Creature.h"

void AnnounceItem(cube::Game* game, cube::Item* item, unsigned int count, cube::Creature* creature)
{
	((void (*)(cube::Game *, cube::Item *, unsigned int, cube::Creature *))CWOffset(0x9D6F0))(game, item, count, creature);
}

void KillCreature(cube::World* world, cube::Creature* creature)
{
	((void (*)(cube::World*, cube::Creature::EntityData*, int))CWOffset(0x2A7CA0))(world, &creature->entity_data, 5);
}

extern "C" void OpenChest(cube::Game* game, cube::Creature* chest) {
	if (chest->entity_data.binary_toggles >> (int)cube::Enums::StateFlags::VisibleOnMap & 1 == 1)
	{
		chest->entity_data.binary_toggles ^= 1 << (int)cube::Enums::StateFlags::VisibleOnMap;
	}

	chest->entity_data.interaction_state = 2;

	//cube::Item item = cube::Item(23, 1);
	//AnnounceItem(game, &item, 1, game->GetPlayer());
	KillCreature(&game->host.world, chest);
}

GETTER_VAR(void*, ASMCheckOpenChest_jmpback);
GETTER_VAR(void*, ASMCheckOpenChest_bail);
__attribute__((naked)) void ASMCheckOpenChest() {
	asm(".intel_syntax \n"

		"cmp byte ptr [rdi + 0x19C], 2 \n"
		"jne 1f \n"

		DEREF_JMP(ASMCheckOpenChest_jmpback)

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
		
		DEREF_JMP(ASMCheckOpenChest_jmpback)

		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMChestOpening_jmpback);
__attribute__((naked)) void ASMChestOpening() {
	asm(".intel_syntax \n"
		// No original code is needed.

		PUSH_ALL
		"mov rdx, rdi \n"
		"mov rcx, rsi \n"

		PREPARE_STACK

		"call OpenChest \n"

		RESTORE_STACK

		POP_ALL

		DEREF_JMP(ASMChestOpening_jmpback)

		".att_syntax \n"
	);
}

void SetupChestOpeningHandler() {
	// Setup asm hook
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x99288, (void*)&ASMChestOpening);
	ASMChestOpening_jmpback = (void*)(base + 0x988C1);

	WriteFarJMP(base + 0x991A3, (void*)&ASMCheckOpenChest);
	ASMCheckOpenChest_jmpback = (void*)(base + 0x991C6);
	ASMCheckOpenChest_bail = (void*)(base + 0x99298);
}

void ChestOpeningInitialize()
{
	SetupChestOpeningHandler();
}