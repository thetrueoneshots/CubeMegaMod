#include "WeaponUpgradeMod.h"

#include "hooks/ModifyWeaponUpgrade.h"
#include "hooks/SmithyInteraction.h"

void WeaponUpgradeMod::Initialize()
{
	SetupWeaponUpgradeModification();
	SetupCreatureInteraction();
}
