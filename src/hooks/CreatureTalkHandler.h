/*
* Hook for letting smithy interaction open the inventory and adaption widget.
*/
#include "cwsdk.h"
#include "../CubeMod.h"
#include "../cwsdk-extension.h"
#include "../hooks.h"

extern "C" int OnTalkToCreature(cube::Game * game, cube::Creature * creature)
{
	for (CubeMod* mod : g_Mods)
	{
		if (mod->OnCreatureTalk(game, creature))
		{
			return 1;
		}
	}
	return 0;
}

GETTER_VAR(void*, ASMOnTalkToCreature_jmpback);
GETTER_VAR(void*, ASMOnTalkToCreature_jmpback2);
GETTER_VAR(void*, ASMOnTalkToCreature_bail);
__attribute__((naked)) void ASMOnTalkToCreature() {
	asm(".intel_syntax \n"

		PUSH_ALL

		"mov rdx, rdi \n"
		"mov rcx, rsi \n"

		PREPARE_STACK

		"call OnTalkToCreature \n"

		RESTORE_STACK

		"cmp rax, 1 \n"
		"je 2f \n"

		POP_ALL

		"cmp al, 2 \n"
		"jbe 1f \n"
		"cmp cl, 0x9C \n"
		"jz 1f \n"
		DEREF_JMP(ASMOnTalkToCreature_jmpback)

		"1: \n"
		DEREF_JMP(ASMOnTalkToCreature_jmpback2)

		"2: \n"
		POP_ALL
		DEREF_JMP(ASMOnTalkToCreature_bail)

		".att_syntax \n"
	);
}


void SetupCreatureInteraction()
{
	WriteFarJMP(CWOffset(0x98D04), &ASMOnTalkToCreature);
	ASMOnTalkToCreature_jmpback = CWOffset(0x98D15);
	ASMOnTalkToCreature_jmpback2 = CWOffset(0x98ED2);
	ASMOnTalkToCreature_bail = CWOffset(0x988C1);
}