/*
* Hook for a new regionlock update.
*/

#pragma once
#include "cwsdk.h"
#include "../hooks.h"

// Todo make function for cubemod.
extern "C" int OnGetEffectiveItemRarity(cube::Item * item, int distance) {
	if (item->category == 2)
	{
		return item->rarity;
	}

	int plus = item->IsPlusItem() ? 1 : 0;
	long long calc = (long long)item->rarity - (long long)((2 - plus) * distance);
	if (calc < 0)
	{
		return -1;
	}
	return (int)calc;
}

__attribute__((naked)) void ASMEffectiveItemRarity() {
	asm(".intel_syntax \n"

		"push r15 \n"
		PUSH_ALL

		"mov rdx, rax \n"
		"mov rcx, r9 \n"

		PREPARE_STACK

		"call OnGetEffectiveItemRarity \n"

		RESTORE_STACK

		"mov [rsp], rax \n"

		POP_ALL

		"mov rax, r15 \n"
		"pop r15 \n"

		"retn \n"
		".att_syntax \n"
	);
}

void SetupRegionLockUpdates() {
	WriteFarJMP(CWOffset(0x10976D), (void*)&ASMEffectiveItemRarity);
	// Change jnz to jo, to always check for the distance.
	WriteByte(CWOffset(0x10974B), 0x70);
	WriteByte(CWOffset(0x109733), 0x70);
}