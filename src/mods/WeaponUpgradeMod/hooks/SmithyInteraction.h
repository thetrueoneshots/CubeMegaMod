/*
* Hook for letting smithy interaction open the inventory and adaption widget.
*/
#include "cwsdk.h"
#include "../../../cwsdk-extension.h"

extern "C" int OnTalkToCreature(cube::Game* game, cube::Creature* creature) 
{
	if (creature->entity_data.classType == (int)cube::Enums::ClassType::Smithy)
	{
		game->gui.adaption_widget->item = nullptr;
		plasma::Display* adaptionWidget = game->gui.adaption_widget->node->display;
		adaptionWidget->SetVisibility(adaptionWidget->visibility.current_frame, 1);

		// Enable enchant widget to avoid chrash
		plasma::Display* characterWidget = game->gui.enchant_widget->node->display;
		characterWidget->SetVisibility(characterWidget->visibility.current_frame, 1);
		
		// Open inventory widget code
		((void (*)(cube::GUI*, int))CWOffset(0x102DB0))(&game->gui, 0);

		// Hide enchant widget again
		characterWidget->SetVisibility(characterWidget->visibility.current_frame, 0);
		return 1;
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
	ASMOnTalkToCreature_bail= CWOffset(0x988C1);

	unsigned char patch[] = {
		0xF3, 0x41, 0x0F, 0x10, 0xF2, 0x90
	};
	
	for (int i = 0; i < 6; i++)
	{
		WriteByte(CWOffset(0x2685D7 + i), patch[i]);
		WriteByte(CWOffset(0x268754 + i), patch[i]);
	}
}

