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
	std::vector<CubeMod*> modVector;
	std::vector<hook::HookEventData> hookEvents;

	/* Hook for the chat function. Triggers when a user sends something in the chat.
	 * @param	{std::wstring*} message
	 * @return	{int}
	*/
	virtual int OnChat(std::wstring* message) override {
		const wchar_t* msg = message->c_str();
		int ID, value;
		if (swscanf_s(msg, L"/mod %d %d", &ID, &value) == 2)
		{
			for (CubeMod* mod : modVector)
			{
				if (mod->m_ID == ID)
				{
					mod->m_Enabled = value == 0 ? false : true;
					if (mod->m_Enabled)
					{
						std::string tmp = "Enabled: ";
						tmp += mod->m_Name;
						Popup("Notice", tmp.c_str());
					}
					else
					{
						std::string tmp = "Disabled: ";
						tmp += mod->m_Name;
						Popup("Notice", tmp.c_str());
					}
				}
			}
			cube::SaveSettings(&modVector);
			return 1;
		}

		for (CubeMod* mod : g_Mods)
		{
			if (mod->OnChat(message))
			{
				return 1;
			}
		}

		// OLD
		/*const wchar_t* msg = message->c_str();

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
		}*/
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
		modVector.push_back(new SeaExplorationMod());
		modVector.push_back(new LoreInteractionMod());
		modVector.push_back(new CombatUpdateMod());

		cube::ApplySettings(&modVector);
		cube::SaveSettings(&modVector);

		// Add enabled mods to the global modlist.
		for (int i = 0; i < modVector.size(); i++)
		{
			if (modVector.at(i)->m_Enabled)
			{
				g_Mods.push_back(modVector.at(i));
			}
		}

		// Modified from https://github.com/ChrisMiuchiz/Cube-World-Mod-Launcher/blob/master/CubeModLoader/main.cpp.
		std::string mods("CubeMegaMods Active:\n");
		for (CubeMod* mod : g_Mods) {
			mods += " - ";
			mods += mod->m_Name;
			mods += " [";
			mods += mod->m_Version.ToString();
			mods += "]\n";
		}
		if (g_Mods.size() == 0) {
			mods += "<No mods>\n";
		}
		Popup("CubeMegaMods", mods.c_str());

		// Setup handlers
		SetupChestInteractionHandler();
		IncreaseLoreInitialize(&hookEvents); // Todo: Rename handler

		for (CubeMod* mod : g_Mods)
		{
			mod->Initialize();
		}

		return;
	}
};

// Export of the mod created in this file, so that the modloader can see and use it.
EXPORT Mod* MakeMod() {
	return new Mod();
}