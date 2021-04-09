#include "NewClassesMod.h"

static NewClassesMod* MOD;
#include "hooks/CharacterCreationHandler.h"
#include "hooks/OnGetUltimateAbilityID.h"
#include "hooks/OnGetUltimateAbilityCooldown.h"
#include "hooks/OnCreatureCanEquipItem.h"
#include "hooks/OnGetShiftAbilityID.h"

#include "classes/MonkClass.h"
#include "classes/TempClass.h"
#include "classes/TempClass2.h"

void NewClassesMod::OnGameTick(cube::Game* game)
{
}

void NewClassesMod::Initialize()
{
	MOD = this;
	m_Classes.push_back(new MonkClass());
	m_Classes.push_back(new TempClass1());
	m_Classes.push_back(new TempClass2());
	InitializeMenuHook();
	InitializeOnGetUltimateIDHandler();
	InitializeOnGetUltimateCooldownHandler();
	InitializeOnCanEquipItemHandler();
	InitializeOnGetShiftIDHandler();

	// Extend menu to supply the amount of classes
	// Add the names of new classes
}
