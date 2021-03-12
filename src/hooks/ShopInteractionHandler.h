/*
* Hook for opening the self made chests. Here, the chests are opened,
* items are added to the player and the gain of the item is announced.
*/

#pragma once
#include "cwsdk.h"

#include "../CubeMod.h"

extern "C" int OnShopInteractionHandler(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, int classType, long long id) {
	for (CubeMod* mod : g_Mods) {
		if (mod->OnShopInteraction(game, itemVector, classType, id)) {
			return 1;
		}
	}
	return 0;
}

GETTER_VAR(void*, ASMShopInteraction_jmpback129);
GETTER_VAR(void*, ASMShopInteraction_jmpback130);
GETTER_VAR(void*, ASMShopInteraction_jmpback156);
GETTER_VAR(void*, ASMShopInteraction_jmpback);
GETTER_VAR(void*, ASMShopInteraction_bail);
__attribute__((naked)) void ASMShopInteractionHandler() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov r9, [rsi+ 0x1E98] \n"
		"mov r8, rdx \n"
		"mov rdx, rdi \n"
		"mov rcx, rsi \n"

		PREPARE_STACK

		"call OnShopInteractionHandler \n"

		RESTORE_STACK

		"test al, al \n"
		"jnz ShopInteractionBail \n"

		POP_ALL

		"mov rcx, r9 \n"
		"sub edx, 0x81 \n"
		"jz 129f \n"
		"sub edx, 0x01 \n"
		"jz 130f \n"
		"cmp edx, 0x1A \n"
		"lea r8, [rsi + 0x1E98] \n"
		"mov rdx, rdi \n"
		"jz 156f \n"

		DEREF_JMP(ASMShopInteraction_jmpback)

		"129: \n"
		DEREF_JMP(ASMShopInteraction_jmpback129)

		"130: \n"
		DEREF_JMP(ASMShopInteraction_jmpback130)

		"156: \n"
		DEREF_JMP(ASMShopInteraction_jmpback156) //Supplier gnome

		"ShopInteractionBail: \n"
		POP_ALL
		DEREF_JMP(ASMShopInteraction_bail)

		".att_syntax \n"
	);
}

void SetupShopInteractionHandler() {
	WriteFarJMP(CWOffset(0xB76CA), (void*)&ASMShopInteractionHandler);

	ASMShopInteraction_jmpback129 = CWOffset(0xB7701);
	ASMShopInteraction_jmpback130 = CWOffset(0xB76F7);
	ASMShopInteraction_jmpback156 = CWOffset(0xB76F0);
	ASMShopInteraction_jmpback = CWOffset(0xB76E9);
	ASMShopInteraction_bail = CWOffset(0xB7709);

	// Patch shop deleting added items
	auto item_vendor_p1 = 0x2ACE17;
	auto item_vendor_p2 = 0x2ACE25;

	auto gem_trader_p1 = 0x2ACC1C;
	auto gem_trader_p2 = 0x2ACC2A;

	for (int i = 0; i < 5; i++)
	{
		WriteByte(CWOffset(gem_trader_p1 + i), 0x90);
		WriteByte(CWOffset(item_vendor_p1 + i), 0x90);
	}

	for (int i = 0; i < 4; i++)
	{
		WriteByte(CWOffset(gem_trader_p2 + i), 0x90);
		WriteByte(CWOffset(item_vendor_p2 + i), 0x90);
	}
}