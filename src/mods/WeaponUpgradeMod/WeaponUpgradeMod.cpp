#include "WeaponUpgradeMod.h"

#include "hooks/ModifyWeaponUpgrade.h"
//#include "hooks/SmithyInteraction.h"

void WeaponUpgradeMod::Initialize()
{
	SetupWeaponUpgradeModification();
	//SetupCreatureInteraction();

	// Patch the button selection of the upgrade window hover code.
	unsigned char patch[] = {
		0xF3, 0x41, 0x0F, 0x10, 0xF2, 0x90
	};

	for (int i = 0; i < 6; i++)
	{
		WriteByte(CWOffset(0x2685D7 + i), patch[i]);
		WriteByte(CWOffset(0x268754 + i), patch[i]);
	}
}

int WeaponUpgradeMod::OnCreatureTalk(cube::Game* game, cube::Creature* creature)
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
