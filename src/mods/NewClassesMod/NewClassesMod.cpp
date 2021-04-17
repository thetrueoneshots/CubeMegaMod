#include "NewClassesMod.h"

static NewClassesMod* MOD;
#include "hooks/CharacterCreationHandler.h"
#include "hooks/OnGetUltimateAbilityID.h"
#include "hooks/OnGetUltimateAbilityCooldown.h"
#include "hooks/OnCreatureCanEquipItem.h"
#include "hooks/OnGetShiftAbilityID.h"
#include "hooks/OnCreaturePassiveMana.h"
#include "hooks/TreasureFixHandler.h"
#include "hooks/OnExecuteAbility.h"

#include "classes/MonkClass.h"

void NewClassesMod::OnGameTick(cube::Game* game)
{
	static bool initialized = false;
	if (!initialized)
	{
		initialized = true;

		// Fix crafting tabs
		char* base = (char*)CWBase();
		int offset = 0x107721;
		WriteByte(base + offset, 0x90);
		WriteByte(base + offset + 0x01, 0x90);
		WriteByte(base + offset + 0x02, 0x90);
		WriteByte(base + offset + 0x03, 0x90);
		WriteByte(base + offset + 0x04, 0x90);
		WriteByte(base + offset + 0x05, 0x90);

		CharacterClass::IntializeAbilities(game);

		int i = 0;
		for (CharacterClass* characterClass : m_Classes)
		{
			characterClass->Initialize(game, i + 5);
			i++;
		}
	}
}

void NewClassesMod::Initialize()
{
	MOD = this;
	m_Classes.push_back(new MonkClass());
	InitializeMenuHook();
	InitializeOnGetUltimateIDHandler();
	InitializeOnGetUltimateCooldownHandler();
	InitializeOnCanEquipItemHandler();
	InitializeOnGetShiftIDHandler();
	InitializeOnCreatureManaHandler();
	InitializeTreasureFixHandler();
	InitializeOnExecuteAbilityHandler();

	// Extend menu to supply the amount of classes
	// Add the names of new classes
}
