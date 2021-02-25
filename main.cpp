#include "main.h"
#include <stdlib.h>

#include "src/cwsdk-extension.h"

// Create global vars here
#include "src/hooks.h"

void SpawnChest(int chest)
{
	if (chest < 0 || chest >= 4)
	{
		return;
	}

	// Todo: Refactor.
	cube::Creature* creature = cube::CreatureFactory::CreateCreature(cube::CreatureTypeBlueFish, 1);
	if (creature != nullptr)
	{
		creature->entity_data.position = cube::GetGame()->GetPlayer()->entity_data.position;
		creature->entity_data.race = 181 + chest;
		creature->entity_data.level = 4;
		creature->entity_data.hostility_type = (int)cube::EntityBehaviour::ExamineObject;
		creature->entity_data.appearance.flags2 |= 1 << (int)cube::AppearanceModifiers::IsPossesed;
		((cube::Creature * (*)(cube::World*, int, cube::Creature*))CWOffset(0x2B67B0))(&cube::GetGame()->host.world, 0, creature);
		cube::CreatureFactory::AddCreatureToWorld(creature);
	}
}

void SpawnFish()
{
	const static int ENTITY_TYPES[13] = {
		106,
		107,
		145,
		146,
		147,
		148,
		149,
		150,
		152,
		153,
		154,
		155,
		295,
	};

	const static int MAX_COUNT = 5;
	int rand = std::rand();
	int cnt = 13;
	
	for (int i = 0; i < cnt; i++)
	{
		// Todo: Refactor
		cube::Creature* creature = cube::CreatureFactory::CreateCreature(cube::CreatureTypeBlueFish, 1);
		if (creature != nullptr)
		{
			creature->entity_data.position = cube::GetGame()->GetPlayer()->entity_data.position;
			creature->entity_data.race = ENTITY_TYPES[i];
			creature->entity_data.level = (rand + i) % 5;
			creature->entity_data.hostility_type = (int)cube::EntityBehaviour::Hostile;
			creature->entity_data.appearance.flags2 |= 1 << (int)cube::AppearanceModifiers::IsFriendly;
			((cube::Creature * (*)(cube::World*, int, cube::Creature*))CWOffset(0x2B67B0))(&cube::GetGame()->host.world, 0, creature);
			cube::CreatureFactory::AddCreatureToWorld(creature);
		}
	}
}

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
		int index = 0;

		if (!wcscmp(msg, L"/init"))
		{
			// Adding 3 Dragon roots
			//cube::Item item = cube::Item(11, 36);
			//cube::ItemStack* stack = new cube::ItemStack(3, item);
			//cube::GetGame()->GetPlayer()->inventory_tabs.at(cube::Inventory::IngredientsTab).push_back(*stack);

			SpawnFish();
		}
		else if (!wcscmp(msg, L"/chest") || swscanf_s(msg, L"/chest %d", &index) == 1)
		{
			SpawnChest(index);
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
		if (flags & (1 << (int)cube::CollisionFlags::Water) && !(flags & (1 << (int)cube::CollisionFlags::Surfaced)))
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