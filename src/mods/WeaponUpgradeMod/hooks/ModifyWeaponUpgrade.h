/* Hook for modifying how weapons get upgraded.
*/
#include "cwsdk.h"

extern "C" void SetWeaponPreview(cube::Item * dest, cube::Item * src) {
	dest->Copy(src);
	dest->UpgradeItem();
	return;
}

GETTER_VAR(void*, ASMWeaponUpgradePreview_jmpback);
__attribute__((naked)) void ASMWeaponUpgradePreview() {
	asm(".intel_syntax \n"

		PUSH_ALL
		"mov rdx, rbx \n"
		"lea rcx, [rbp+0x100] \n"

		PREPARE_STACK

		"call SetWeaponPreview \n"

		RESTORE_STACK

		POP_ALL

		DEREF_JMP(ASMWeaponUpgradePreview_jmpback)

		".att_syntax \n"
	);
}

void SetupWeaponUpgradeModification()
{
	WriteFarJMP(CWOffset(0x267BD5), &ASMWeaponUpgradePreview);
	ASMWeaponUpgradePreview_jmpback = CWOffset(0x267C89);
}