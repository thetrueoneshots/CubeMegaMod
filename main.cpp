#include "main.h"
#include <stdlib.h>

#include "src/cwsdk-extension.h"

#include "src/mods/SeaExplorationMod/SeaExplorationMod.h"
#include "src/mods/LoreInteractionMod/LoreInteractionMod.h"
#include "src/mods/CombatUpdatesMod/CombatUpdateMod.h"
#include "src/mods/CreatureUpdatesMod/CreatureUpdatesMod.h"
#include "src/mods/GemTraderMod/GemTraderMod.h"
#include "src/CubeMod.h"

GLOBAL std::vector<CubeMod*> g_Mods;
GLOBAL char* g_Base;

#include "src/hooks/ChestInteractionHandler.h"
#include "src/hooks/ShopInteractionHandler.h"
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

		if (!wcscmp(msg, L"/supplier"))
		{
			cube::Creature* player = cube::GetGame()->GetPlayer();
			cube::Creature* creature = cube::CreatureFactory::SpawnCreature(player->entity_data.position, player->entity_data.current_region,
				304, (int)cube::Enums::EntityBehaviour::NPC, 1);
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::NeededForGemTrader;
			creature->entity_data.classType = (int)cube::Enums::ClassType::GemTrader;
			
			
			/*creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::IsUseable;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::IsClassMaster;
			creature->entity_data.classType = 0;
			creature->entity_data.specialization = 1;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_01;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_02;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_03;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_04;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_05;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_07;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_08;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_11;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_12;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_16;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_19;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_23;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_24;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_25;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_27;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_28;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_29;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_30;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::Enums::AppearanceModifiers::Unk_31;*/

			return 1;
		}

		// Test
		if (!wcscmp(msg, L"/test"))
		{
			wchar_t buffer[250];
			swprintf_s(buffer, 250, L"Player: %#012X\n", cube::GetGame()->GetPlayer());
			cube::GetGame()->PrintMessage(buffer, 0, 255, 100);

			for (cube::Creature* creature : cube::GetGame()->host.world.creatures)
			{
				if (creature->entity_data.race == 304)
				{
					swprintf_s(buffer, 250, L"Supplier gnome: %#012X\n", creature);
					cube::GetGame()->PrintMessage(buffer, 0, 255, 100);
				}
			}
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
		modVector.push_back(new CreatureUpdatesMod());
		modVector.push_back(new GemTraderMod());

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
		SetupShopInteractionHandler();
		IncreaseLoreInitialize(&hookEvents); // Todo: Rename handler

		for (CubeMod* mod : g_Mods)
		{
			mod->Initialize();
		}

		return;
	}

	void OnCreatureArmorCalculated(cube::Creature* creature, float* armor)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureArmorCalculated(creature, armor);
		}
	}

	void OnCreatureCriticalCalculated(cube::Creature* creature, float* critical)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureCriticalCalculated(creature, critical);
		}
	}

	void OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureAttackPowerCalculated(creature, power);
		}
	}

	void OnCreatureSpellPowerCalculated(cube::Creature* creature, float* power)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureSpellPowerCalculated(creature, power);
		}
	}

	void OnCreatureHasteCalculated(cube::Creature* creature, float* haste)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureHasteCalculated(creature, haste);
		}
	}

	void OnCreatureHPCalculated(cube::Creature* creature, float* hp)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureHPCalculated(creature, hp);
		}
	}

	void OnCreatureResistanceCalculated(cube::Creature* creature, float* resistance)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureResistanceCalculated(creature, resistance);
		}
	}

	void OnCreatureRegenerationCalculated(cube::Creature* creature, float* regeneration)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureRegenerationCalculated(creature, regeneration);
		}
	}

	void OnCreatureManaGenerationCalculated(cube::Creature* creature, float* manaGeneration)
	{
		for (CubeMod* mod : g_Mods)
		{
			mod->OnCreatureManaGenerationCalculated(creature, manaGeneration);
		}
	}
};

// Export of the mod created in this file, so that the modloader can see and use it.
EXPORT Mod* MakeMod() {
	return new Mod();
}