#include "main.h"
#include <stdlib.h>

#include "src/cwsdk-extension.h"

#include "src/mods/SeaExplorationMod/SeaExplorationMod.h"
#include "src/mods/LoreInteractionMod/LoreInteractionMod.h"
#include "src/mods/CombatUpdatesMod/CombatUpdateMod.h"
#include "src/CubeMod.h"

GLOBAL std::vector<CubeMod*> g_Mods;
GLOBAL char* g_Base;

#include "src/hooks/ChestInteractionHandler.h"
#include "src/hooks/lore_increase.h"

// OLD
#define DEBUG 1

// OLD
int DisplayOnlyInDebugMessage()
{
	cube::GetGame()->PrintMessage(L"[Error] This command is only available in debug mode.\n", 255, 127, 80);
	return 1;
}

/* Mod class containing all the functions for the mod.
*/
class Mod : GenericMod {
	// OLD
	std::vector<hook::HookEventData> hookEvents;
	cube::FileVariables settings;
	/* Hook for the chat function. Triggers when a user sends something in the chat.
	 * @param	{std::wstring*} message
	 * @return	{int}
	*/
	virtual int OnChat(std::wstring* message) override {
		for (CubeMod* mod : g_Mods)
		{
			if (mod->OnChat(message))
			{
				return 1;
			}
		}

		// OLD
		const wchar_t* msg = message->c_str();

		cube::Creature* player = cube::GetGame()->GetPlayer();
		int index = 0;
		int count = 1;
		if (swscanf_s(msg, L"/ability %d", &index) == 1)
		{
			if (!DEBUG)
			{
				return DisplayOnlyInDebugMessage();
			}
			cube::Ability::CWAbility(player, index);
			return 1;
		}

		if (!wcscmp(msg, L"/enable doubletap"))
		{
			settings.m_DoubleTapActivated = true;
			cube::WriteSettingsFile(settings);
		}

		if (!wcscmp(msg, L"/enable autogoldusage"))
		{
			settings.m_AutomaticGoldConsumptionActivated = true;
			cube::WriteSettingsFile(settings);
		}

		if (!wcscmp(msg, L"/disable autogoldusage"))
		{
			settings.m_AutomaticGoldConsumptionActivated = false;
			cube::WriteSettingsFile(settings);
		}


		if (!wcscmp(msg, L"/disable doubletap"))
		{
			settings.m_DoubleTapActivated = false;
			cube::WriteSettingsFile(settings);
		}

		if (swscanf_s(msg, L"/drop %d %d", &index, &count) == 2 || swscanf_s(msg, L"/drop %d", &index) == 1)
		{
			if (!DEBUG)
			{
				return DisplayOnlyInDebugMessage();
			}
			cube::Helper::DropItem(
				player, 
				(cube::Helper::ItemGenerationType)index,
				count
			);
			return 1;
		}

		if (!wcscmp(msg, L"/fish") || swscanf_s(msg, L"/fish %d", &index) == 1)
		{
			if (!DEBUG)
			{
				return DisplayOnlyInDebugMessage();
			}
			cube::CreatureFactory::SpawnFishes(index);
		}
		else if (!wcscmp(msg, L"/roots"))
		{
			if (!DEBUG)
			{
				return DisplayOnlyInDebugMessage();
			}
			// Adding 3 Dragon roots
			cube::Item item = cube::Item(11, 36);
			cube::ItemStack stack = cube::ItemStack(60, item);
			cube::GetGame()->GetPlayer()->inventory_tabs.at(cube::Inventory::IngredientsTab).push_back(stack);
		}
		else if (!wcscmp(msg, L"/chest") || swscanf_s(msg, L"/chest %d", &index) == 1)
		{
			if (!DEBUG)
			{
				return DisplayOnlyInDebugMessage();
			}
			cube::CreatureFactory::SpawnChest(player->entity_data.position, player->entity_data.current_region, index);
		}
		return 0;
	}

	/* Function hook that gets called every game tick.
	 * @param	{cube::Game*} game
	 * @return	{void}
	*/
	virtual void OnGameTick(cube::Game* game) override {
		for (CubeMod* mod : g_Mods) {
			mod->OnGameTick(game);
		}

		for (hook::HookEventData e : hookEvents)
		{
			switch (e.type)
			{
			case hook::HookEvent::LoreInteraction:
				for (CubeMod* mod : g_Mods) {
					mod->OnLoreIncrease(game, e.data);
				}
			default:
				break;
			}
		}
		hookEvents.clear();

		return;
	}

	void OnGetKeyboardState(BYTE* diKeys) override {
		for (CubeMod* mod : g_Mods)
		{
			mod->OnGetKeyboardState(diKeys);
		}
	}

	/* Function hook that gets called on intialization of cubeworld.
	 * [Note]:	cube::GetGame() is not yet available here!!
	 * @return	{void}
	*/
	virtual void Initialize() override {
		g_Base = (char*)CWBase();
		g_Mods.push_back(new SeaExplorationMod());
		g_Mods.push_back(new LoreInteractionMod());
		g_Mods.push_back(new CombatUpdateMod());

		// Setup handlers
		SetupChestInteractionHandler();
		IncreaseLoreInitialize(&hookEvents); // Todo: Rename handler

		for (CubeMod* mod : g_Mods)
		{
			mod->Initialize();
		}

		//settings = cube::ReadSettingsFile();
		//cube::WriteSettingsFile(settings);

		return;
	}
};

// Export of the mod created in this file, so that the modloader can see and use it.
EXPORT Mod* MakeMod() {
	return new Mod();
}