/*
* Hook for modifying the ultimate ability ID.
*/
#pragma once

#include "cwsdk.h"
#include "../NewClassesMod.h"

extern "C" int OnCreatureManaModification(cube::Creature* player) {
	if (player->entity_data.classType <= 4)
	{
		return 0;
	}

	int index = player->entity_data.classType - 5;
	if (index < 0 || index >= MOD->m_Classes.size())
	{
		return 0;
	}

	return MOD->m_Classes.at(index)->ManaGenerationType(player);
}

GETTER_VAR(void*, ASMOnManaHandler_jmpback);
__attribute__((naked)) void ASMOnManaHandler() {
	asm(".intel_syntax \n"
		"movaps xmm1, xmm10 \n"
		"mulss xmm1, xmm12 \n"
		"movss xmm0, dword ptr [r13 + 0x188] \n"

		PUSH_ALL
		PREPARE_STACK
		"mov rcx, r13 \n"
		"call OnCreatureManaModification \n"
		RESTORE_STACK
		"cmp rax, 0 \n"
		"je 1f \n"
		"cmp rax, 1 \n"
		"je 2f \n"
		POP_ALL
		// Nothing
		DEREF_JMP(ASMOnManaHandler_jmpback)

		"1: \n"
		POP_ALL
		// Original code, mana loss
		"subss xmm0, xmm1\n"
		DEREF_JMP(ASMOnManaHandler_jmpback)

		"2: \n"
		POP_ALL
		// Mana gain
		"addss xmm0, xmm1 \n"
		DEREF_JMP(ASMOnManaHandler_jmpback)
		

		".att_syntax \n"
	);
}

void InitializeOnCreatureManaHandler()
{
	WriteFarJMP(CWOffset(0x2DFDBC), (void*)&ASMOnManaHandler);
	ASMOnManaHandler_jmpback = CWOffset(0x2DFDD2);
}