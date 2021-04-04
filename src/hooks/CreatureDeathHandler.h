/*
* Hook for creature on death.
*/
#include "../hooks.h"
#include <string>

extern "C" void OnCreatureDeath(cube::Creature * creature, cube::Creature * attacker) {
	for (CubeMod* mod : g_Mods) {
		mod->OnCreatureDeath(creature, attacker);
	}
	return;
}

GETTER_VAR(void*, ASMOnCreatureDeath_jmpback);
__attribute__((naked)) void ASMOnCreatureDeath() {
	asm(".intel_syntax \n"
		
		PUSH_ALL
		"mov rdx, r15 \n" // attacker (can also be rsi)
		"mov rcx, r13 \n" // dead creature

		PREPARE_STACK

		"call OnCreatureDeath \n"

		RESTORE_STACK

		POP_ALL

		// old code
		"xor r15d, r15d \n"
		"mov [r13 + 0x180], r15 \n" //HP to 0
		"mov dword ptr [rbp - 0x41], 0x3F800000 \n" //Something with sound

		DEREF_JMP(ASMOnCreatureDeath_jmpback)
		".att_syntax \n"
	);
}

void SetupOnCreatureDeathHandler()
{
	WriteFarJMP(CWOffset(0x29E494), ASMOnCreatureDeath);
	ASMOnCreatureDeath_jmpback = CWOffset(0x29E4A5);
}