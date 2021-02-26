#include "main.h"
#include <stdlib.h>

#include "src/cwsdk-extension.h"

// Create global vars here
#include "src/hooks.h"

/* Mod class containing all the functions for the mod.
*/
class Mod : GenericMod {

	cube::EventList eventList;
	/* Hook for the chat function. Triggers when a user sends something in the chat.
	 * @param	{std::wstring*} message
	 * @return	{int}
	*/
	virtual int OnChat(std::wstring* message) override {
		const wchar_t* msg = message->c_str();

		cube::Creature* player = cube::GetGame()->GetPlayer();
		int index = 0;

		if (!wcscmp(msg, L"/fish") || swscanf_s(msg, L"/fish %d", &index) == 1)
		{
			cube::CreatureFactory::SpawnFishes(index);
		}

		else if (!wcscmp(msg, L"/roots"))
		{
			// Adding 3 Dragon roots
			cube::Item item = cube::Item(11, 36);
			cube::ItemStack stack = cube::ItemStack(3, item);
			cube::GetGame()->GetPlayer()->inventory_tabs.at(cube::Inventory::IngredientsTab).push_back(stack);
		}
		else if (!wcscmp(msg, L"/chest") || swscanf_s(msg, L"/chest %d", &index) == 1)
		{
			cube::CreatureFactory::SpawnChest(player->entity_data.position, player->entity_data.current_region, index);
		}
		return 0;
	}

	/* Function hook that gets called every game tick.
	 * @param	{cube::Game*} game
	 * @return	{void}
	*/
	virtual void OnGameTick(cube::Game* game) override {
		static bool initialized = false;
		if (!initialized)
		{
			initialized = true;
			eventList.Add(new cube::AddGoldEvent());
		}

		// Check for DivingEvent
		unsigned int flags = game->GetPlayer()->entity_data.flags;
		if (flags & (1 << (int)cube::Enums::CollisionFlags::Water) && !(flags & (1 << (int)cube::Enums::CollisionFlags::Surfaced)))
		{
			if (!eventList.Find(cube::EventType::Diving))
			{
				eventList.Add(new cube::DivingEvent());
			}
		}
		else
		{
			eventList.Remove(cube::EventType::Diving);
		}
		
		// Update all events
		for (cube::Event* e : eventList.events)
		{
			e->Update();
		}
		
		return;
	}

	/* Function hook that gets called on intialization of cubeworld.
	 * [Note]:	cube::GetGame() is not yet available here!!
	 * @return	{void}
	*/
	virtual void Initialize() override {

		hook::InitializeAll();
		hook::DisableCreatureFloating();

		cube::DivingEvent::Initialize();
		return;
	}
};

// Export of the mod created in this file, so that the modloader can see and use it.
EXPORT Mod* MakeMod() {
	return new Mod();
}