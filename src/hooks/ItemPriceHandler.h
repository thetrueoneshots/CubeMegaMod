/*
* Hook for opening the self made chests. Here, the chests are opened,
* items are added to the player and the gain of the item is announced.
*/

#pragma once
#include "cwsdk.h"

#include "../CubeMod.h"

extern "C" void OnItemPriceHandler(cube::Item* item, int* price) {
	//for (CubeMod* mod : g_Mods) {
	//	mod->OnItemPrice(item, price);
	//}
	// Todo: Create a CubeMod function that gets called for every mod.
	switch (item->category)
	{
	case 1:
		if (item->id == 1)
		{
			*price = 5 * (item->rarity + 1);
		}
		break;
	case 11:
		if (item->id == 14)
		{
			*price = 25;
		}
		break;
	case 23:
		*price = 1000;
		break;
	case 24:
		if (item->id > 13 && item->id < 18)
		{
			*price = 25 * (item->id - 13);
		}
		else if (item->id == 12)
		{
			*price = 25;
		}
		else
		{
			*price = 75;
		}
		break;
	default:

		break;
	}
}

GETTER_VAR(void*, ASMItemPrice_jmpback);
__attribute__((naked)) void ASMItemPriceHandler() {
	asm(".intel_syntax \n"
		// Old code
		"mov     eax, 1 \n"
		"cvttss2si ecx, xmm0 \n"
		"cmp     ecx, eax \n"
		"cmovg   eax, ecx \n"

		PUSH_ALL
		// Load price pointer
		"push rax \n"
		"lea rdx, [rsp] \n"
		"mov rcx, r8 \n"

		PREPARE_STACK

		"call OnItemPriceHandler \n"

		RESTORE_STACK

		"pop rax \n"
		"movq xmm0, rax \n"

		POP_ALL

		"movq rax, xmm0 \n"

		// Old code
		"movaps  xmm6, xmmword ptr[rsp + 0x20] \n"
		"add     rsp, 0x38 \n"

		DEREF_JMP(ASMItemPrice_jmpback)
		".att_syntax \n"
	);
}

void SetupItemPriceHandler() {
	WriteFarJMP(CWOffset(0x109E17), (void*)&ASMItemPriceHandler);
	ASMItemPrice_jmpback = CWOffset(0x109E2E);
}