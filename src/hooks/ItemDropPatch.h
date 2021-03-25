/*
* Hook for opening the self made chests. Here, the chests are opened,
* items are added to the player and the gain of the item is announced.
*/

#pragma once
#include "cwsdk.h"

IntVector2* GetPlayerRegion(void)
{
	return &cube::GetGame()->GetPlayer()->entity_data.current_region;
}

extern "C" IntVector2* GetDropRegion(void) {
	return GetPlayerRegion();
}

GETTER_VAR(void*, ASMPatchItemDrop_jmpback);
__attribute__((naked)) void ASMPatchItemDrop() {
	asm(".intel_syntax \n"

		"push r15 \n"

		PUSH_ALL

		PREPARE_STACK

		"call GetDropRegion \n"

		RESTORE_STACK

		//"mov rax, [rax] \n"
		"mov [rsp], rax \n"
		
		POP_ALL

		"mov rax, r15 \n"
		"pop r15 \n"
		"mov rcx, rax \n"
		//"mov eax, [rax] \n"

		DEREF_JMP(ASMPatchItemDrop_jmpback)

		".att_syntax \n"
	);
}

void ItemDropPatchInitialize() {
	// Setup asm hook
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x2A5E2E, (void*)&ASMPatchItemDrop);
	WriteByte(CWOffset(0x2A5E3C), 0x90);
	ASMPatchItemDrop_jmpback = (void*)(base + 0x2A5E3D);
}