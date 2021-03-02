/*
* Hook for adding lore. This will check whatever the current value is and
* act on it accordingly.
*/

#pragma once

#include "cwsdk.h"

#include "../cwsdk-extension/creature/Creature.h"

static std::vector<hook::HookEvent>* hookEvents;
const static int LORE_LEVELUP_THRESHHOLD = 100;

extern "C" void OnPrintRGBA(std::wstring* message) {
	const wchar_t* msg = message->c_str();
	int index = 0;

	if (swscanf_s(msg, L" lore increased to %d", &index) == 1)
	{
		if (index >= LORE_LEVELUP_THRESHHOLD)
		{
			//cube::Creature* player = cube::GetGame()->GetPlayer();
			//cube::Helper::LevelUp(player);
			hookEvents->push_back(hook::HookEvent::LevelUp);
		}
		return;
	}
}

GETTER_VAR(void*, ASMIncreaseLore_jmpback);
__attribute__((naked)) void ASMIncreaseLore() {
	asm(".intel_syntax \n"

		PUSH_ALL

		"mov rcx, rdx \n"

		PREPARE_STACK

		"call OnPrintRGBA \n"

		RESTORE_STACK

		POP_ALL

		// Original code
		"mov rbx, rdx \n"
		"mov r13, rcx \n"
		"xor edi, edi \n"
		"mov r15d, edi \n"
		"mov [rsp + 0x70], rdi \n"
		"mov [rsp + 0x78], rdi \n"

		DEREF_JMP(ASMIncreaseLore_jmpback)

		".att_syntax \n"
	);
}

void SetupIncreaseLoreHandler() {
	// Setup asm hook
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x26B6C4, (void*)&ASMIncreaseLore);
	ASMIncreaseLore_jmpback = (void*)(base + 0x26B6D9);
}

void IncreaseLoreInitialize(std::vector<hook::HookEvent>* events)
{
	hookEvents = events;
	SetupIncreaseLoreHandler();
}