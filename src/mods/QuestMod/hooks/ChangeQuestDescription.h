/*
* Hook for letting smithy interaction open the inventory and adaption widget.
*/
#include <string>
#include "cwsdk.h"
#include "../../../cwsdk-extension.h"

extern "C" int OnGetItemDescription(cube::BaseWidget* widget, cube::Item* item, FloatVector2* pos)
{
	if (item->category == 2)
	{
		std::wstring text;
		cube::Quest* quest = (cube::Quest*)item;
		text = *quest->GetQuestName(&cube::GetGame()->speech, &text);

		FloatRGBA color(1.f, .25f, 0.25f, 1.f);
		widget->SetDrawColor(&color);
		widget->DrawBaseWidgetText(pos, &text, pos->x, pos->y);

		color = { 1.f, 1.f, 1.f, 1.f };
		text = *quest->GetQuestDescription(&cube::GetGame()->speech, &text);
		widget->SetDrawColor(&color);
		widget->DrawBaseWidgetText(pos, &text, pos->x, pos->y);
		
		return 1;
	}
	return 0;
}

GETTER_VAR(void*, ASMOnGetItemDescription_jmpback);
GETTER_VAR(void*, ASMOnGetItemDescription_jmpback_2);
GETTER_VAR(void*, ASMOnGetItemDescription_bail);
__attribute__((naked)) void ASMOnGetItemDescription() {
	asm(".intel_syntax \n"

		// old code
		"movss dword ptr [rsi + 0x1B0], xmm13 \n"

		PUSH_ALL

		"mov rcx, rsi \n"
		"mov rdx, r14 \n"
		"mov r8, rdi \n"

		PREPARE_STACK

		"call OnGetItemDescription \n"

		RESTORE_STACK

		"cmp rax, 1 \n"
		"je 1f \n"

		POP_ALL

		// old code
		"cmp byte ptr[r14], 0x01 \n"
		"jnz 2f \n"

		DEREF_JMP(ASMOnGetItemDescription_jmpback)

		"2: \n"

		DEREF_JMP(ASMOnGetItemDescription_jmpback_2)

		"1: \n" // bail
		POP_ALL

		"movss xmm0, xmm10 \n"
		DEREF_JMP(ASMOnGetItemDescription_jmpback_2)

		".att_syntax \n"
	);
}

void SetupOnGetItemDescription()
{
	WriteFarJMP(CWOffset(0xBA33B), &ASMOnGetItemDescription);
	ASMOnGetItemDescription_jmpback = CWOffset(0xBA351);
	ASMOnGetItemDescription_jmpback_2 = CWOffset(0xBA478);
	ASMOnGetItemDescription_bail = CWOffset(0xBA363);
}

