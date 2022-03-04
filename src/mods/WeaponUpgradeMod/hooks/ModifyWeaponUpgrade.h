/* Hook for modifying how weapons get upgraded.
*/
#include "cwsdk.h"

extern "C" void SetWeaponPreview(cube::Item * dest, cube::Item * src) {
	dest->Copy(src);
	dest->UpgradeItem();
	return;
}

extern "C" void UpgradeWeapon(cube::AdaptionWidget * widget) {
	widget->game->PrintMessage(L"Upgrading! \n");

	cube::Item* item = widget->item;
	cube::Creature* player = widget->game->GetPlayer();
	int price = item->GetBuyingPrice();
	if (price > player->gold)
	{
		return;
	}

	player->gold -= price;
	item->UpgradeItem();
	widget->game->AnnounceReceiptOfItem(item);
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

__attribute__((naked)) void ASMOnWeaponUpgrade() {
	asm(".intel_syntax \n"

		PUSH_ALL

		PREPARE_STACK

		"call UpgradeWeapon \n"

		RESTORE_STACK

		POP_ALL

		"retn \n"
		".att_syntax \n"
	);
}

void SetupWeaponUpgradeModification()
{
	WriteFarJMP(CWOffset(0x267BD5), &ASMWeaponUpgradePreview);
	ASMWeaponUpgradePreview_jmpback = CWOffset(0x267C89);

	WriteFarJMP(CWOffset(0x267930), &ASMOnWeaponUpgrade);
}