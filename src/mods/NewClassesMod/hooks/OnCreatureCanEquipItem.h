/*
* Hook for modifying the ultimate ability ID.
*/
#pragma once

#include "cwsdk.h"
#include "../NewClassesMod.h"

extern "C" int OnCanEquipItem(cube::Item* item, int classType) {
	if (classType <= 4)
	{
		return 0;
	}

	int index = classType - 5;
	if (index < 0 || index >= MOD->m_Classes.size())
	{
		return 0;
	}

	return MOD->m_Classes.at(index)->CanEquipItem(item);
}

GETTER_VAR(void*, ASMOnCanEquipItem_jmpback);
GETTER_VAR(void*, ASMOnCanEquipItem_jmpback_2);
GETTER_VAR(void*, ASMOnCanEquipItem_bail);
__attribute__((naked)) void ASMOnCanEquipItem() {
	asm(".intel_syntax \n"
		PUSH_ALL
		PREPARE_STACK
		"call OnCanEquipItem \n"
		RESTORE_STACK
		"cmp rax, 0 \n"
		"jne 1f \n"
		POP_ALL
		// Original code
		"movzx eax, byte ptr [rcx] \n"
		"mov r9, rcx \n"
		"cmp al, 2 \n"
		"je 2f \n"
		DEREF_JMP(ASMOnCanEquipItem_jmpback)

		"2: \n"
		DEREF_JMP(ASMOnCanEquipItem_jmpback_2)

		"1: \n"
		POP_ALL
		DEREF_JMP(ASMOnCanEquipItem_bail)

		".att_syntax \n"
	);
}

void InitializeOnCanEquipItemHandler()
{
	WriteFarJMP(CWOffset(0x1094E9), (void*)&ASMOnCanEquipItem);
	ASMOnCanEquipItem_jmpback = CWOffset(0x1094F7);
	ASMOnCanEquipItem_jmpback_2 = CWOffset(0x1095CF);
	ASMOnCanEquipItem_bail = CWOffset(0x109677);
}