/*
* Hook for letting smithy interaction open the inventory and adaption widget.
*/
#include <string>
#include "cwsdk.h"
#include "../../../cwsdk-extension.h"

extern "C" int OnGetItemName(cube::Speech* speech, cube::Item* item, cube::Item* copy)
{
	if (item->category == 2)
	{
		int id = item->modifier % 4;
		*copy = cube::Item(1, 15 + id);
		return 1;
	}
	return 0;
}

GETTER_VAR(void*, ASMOnGetItemName_jmpback);
GETTER_VAR(void*, ASMOnGetItemName_bail);
__attribute__((naked)) void ASMOnGetItemName() {
	asm(".intel_syntax \n"

		PUSH_ALL

		"mov rdx, r8 \n"
		"lea r8, [rbp + 0x1E0] \n"

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
	ASMOnGetItemName_bail = CWOffset(0x1629A4);
}

