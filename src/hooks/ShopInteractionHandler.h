/*
* Hook for opening the self made chests. Here, the chests are opened,
* items are added to the player and the gain of the item is announced.
*/

#pragma once
#include "cwsdk.h"

#include "../CubeMod.h"

extern "C" void OnShopInteractionHandler(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, int classType, long long id) {
	std::vector<std::vector<cube::ItemStack >> temp;
	temp.push_back(std::vector<cube::ItemStack>());

	bool clear = false;
	for (CubeMod* mod : g_Mods) {
		if (mod->OnShopInteraction(game, &temp, classType, id)) {
			clear = true;
		}
	}

	if (clear)
	{
		itemVector->at(0).clear();
	}

	for (auto i : temp.at(0))
	{
		itemVector->at(0).push_back(i);
	}
}

extern "C" void ShopInteractionSub1(void* p1, void* p2)
{
	((void (*)(void*, void*))CWOffset(0x64F30))(p1, p2);
}

extern "C" void ShopInteractionSub2(void* p1)
{
	((void (*)(void*))CWOffset(0x280A40))(p1);
}

GETTER_VAR(void*, ASMShopInteraction_jmpback);
__attribute__((naked)) void ASMShopInteractionHandler() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov r9, [rsi+ 0x1E98] \n"
		"mov r8, [rsi+ 0x1EA0] \n"
		"mov rdx, rdi \n"
		"mov rcx, rsi \n"

		PREPARE_STACK

		"call OnShopInteractionHandler \n"

		RESTORE_STACK

		POP_ALL
													 
		"mov     edx, 2 \n"
		"mov     rcx, rdi \n"
		"call    ShopInteractionSub1 \n"
		"mov     rcx, [rsi + 0x350] \n"
		"call    ShopInteractionSub2 \n"

		DEREF_JMP(ASMShopInteraction_jmpback)

		".att_syntax \n"
	);
}

void SetupShopInteractionHandler() {
	WriteFarJMP(CWOffset(0xB7709), (void*)&ASMShopInteractionHandler);
	ASMShopInteraction_jmpback = CWOffset(0xB7722);
}