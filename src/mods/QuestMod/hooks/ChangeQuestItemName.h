/*
* Hook for letting smithy interaction open the inventory and adaption widget.
*/
#include "cwsdk.h"
#include "../../../cwsdk-extension.h"

extern "C" int OnGetItemName(cube::Speech* speech, std::wstring* string, cube::Item* item)
{
	if (item->category == 2)
	{
		string = new std::wstring(L"Hey");
		return 1;
	}
	return 0;
}

GETTER_VAR(void*, ASMOnGetItemName_jmpback);
GETTER_VAR(void*, ASMOnGetItemName_bail);
__attribute__((naked)) void ASMOnGetItemName() {
	asm(".intel_syntax \n"

		PUSH_ALL

		PREPARE_STACK

		"call OnGetItemName \n"

		RESTORE_STACK

		"cmp rax, 1 \n"
		"je 1f \n"

		POP_ALL

		// old code
		"mov rsi, rdx \n"
		"mov [rbp + 0x40], rdx \n"
		"mov rdi, rcx \n"
		"mov [rbp + 0x160], rcx \n"

		DEREF_JMP(ASMOnGetItemName_jmpback)

		"1: \n"
		POP_ALL

		// old code
		"mov rsi, rdx \n"
		"mov [rbp + 0x40], rdx \n"
		"mov rdi, rcx \n"
		"mov [rbp + 0x160], rcx \n"

		DEREF_JMP(ASMOnGetItemName_bail)

		".att_syntax \n"
	);
}

// Todo: Call for every mod
void SetupOnGetItemName()
{
	WriteFarJMP(CWOffset(0x1628E4), &ASMOnGetItemName);
	ASMOnGetItemName_jmpback = CWOffset(0x1628F5);
	ASMOnGetItemName_bail = CWOffset(0x16466C);
}

