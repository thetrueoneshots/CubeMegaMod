#include "main.h"
#include <stdlib.h>

#include "src/cwsdk-extension.h"

// Create global vars here
#include "src/hooks.h"

/* Mod class containing all the functions for the mod.
*/
class Mod : GenericMod {
	std::vector<hook::HookEvent> hookEvents;
	cube::EventList eventList;
	/* Hook for the chat function. Triggers when a user sends something in the chat.
	 * @param	{std::wstring*} message
	 * @return	{int}
	*/
	virtual int OnChat(std::wstring* message) override {
		const wchar_t* msg = message->c_str();

		cube::Creature* player = cube::GetGame()->GetPlayer();
		int index = 0;
		int count = 1;
		if (swscanf_s(msg, L"/ability %d", &index) == 1)
		{
			cube::Ability::CWAbility(player, index);
			return 1;
		}

		if (swscanf_s(msg, L"/drop %d %d", &index, &count) == 2 || swscanf_s(msg, L"/drop %d", &index) == 1)
		{
			//cube::Helper::LevelUp(player);
			cube::Helper::DropItem(
				player, 
				(cube::Helper::ItemGenerationType)index,
				count
			);
			return 1;
		}

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
		static long cnt = 0;
		cnt++;
		if (cnt > 360)
			cnt = 0;
		static bool initialized = false;
		if (!initialized)
		{
			initialized = true;
			eventList.Add(new cube::AddGoldEvent());
			game->screen_shake = true;

		}

		//game->camera_angle.z = 180;

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

		for (hook::HookEvent e : hookEvents)
		{
			switch (e)
			{
			case hook::HookEvent::LevelUp:
				cube::Helper::LevelUp(cube::GetGame()->GetPlayer());
				break;
			default:

				break;
			}
		}
		hookEvents.clear();

		return;
	}

	void OnGetKeyboardState(BYTE* diKeys) override {
		static DButton KeyW(17); //W
		static DButton KeyA(30); //A
		static DButton KeyS(31); //S
		static DButton KeyD(32); //D

		static DButton Key1(2); //1
		static DButton Key2(3); //2

		if (cube::Helper::InGUI(cube::GetGame()))
		{
			return;
		}

		KeyW.Update(diKeys);
		KeyA.Update(diKeys);
		KeyS.Update(diKeys);
		KeyD.Update(diKeys);

		Key1.Update(diKeys);
		Key2.Update(diKeys);

		cube::Creature* player = cube::GetGame()->GetPlayer();

		if (Key1.Pressed())
		{
			cube::ConvertMTSAbility().Execute(player);
		}
		if (Key2.Pressed())
		{
			cube::HealAbility().Execute(player);
		}

		if (KeyW.Pressed() == 2)
		{
			cube::FarJumpAbility(0).Execute(player);
		}

		if (KeyA.Pressed() == 2)
		{
			cube::FarJumpAbility(1).Execute(player);
		}

		if (KeyS.Pressed() == 2)
		{
			cube::FarJumpAbility(3).Execute(player);
		}

		if (KeyD.Pressed() == 2)
		{
			cube::FarJumpAbility(2).Execute(player);
		}
	}

	/* Function hook that gets called on intialization of cubeworld.
	 * [Note]:	cube::GetGame() is not yet available here!!
	 * @return	{void}
	*/
	virtual void Initialize() override {

		hook::InitializeAll(&hookEvents);
		hook::DisableCreatureFloating();

		cube::DivingEvent::Initialize();
		return;
	}
};

// Export of the mod created in this file, so that the modloader can see and use it.
EXPORT Mod* MakeMod() {
	return new Mod();
}