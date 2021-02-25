#include "main.h"
#include <stdlib.h>

#include "src/cwsdk-extension.h"

static int bit = 0;

// Create global vars here
#include "src/hooks.h"

/*cube::Creature* SpawnCreature(const LongVector3& position, int entityType, int entityBehaviour, int level)
{
	cube::Creature* creature = cube::Creature::Create(cube::CreatureFactory::GenerateId());
	if (creature != nullptr)
	{
		creature->entity_data.position = position;

		cube::CreatureFactory::SetAppearance(creature, entityType, entityBehaviour, level);
		cube::CreatureFactory::AddCreatureToWorld(creature);
	}
	return creature;
}
*/
/*cube::Creature* SpawnChest(const LongVector3& position, float rotationY, int chestType, int level)
{
	if (chestType < 0 || chestType >= 4)
	{
		return;
	}

	if (level < 0)
	{
		return;
	}

	cube::Creature* creature = SpawnCreature(position, 181 + chestType, (int)cube::Enums::EntityBehaviour::ExamineObject, level);
	if (creature != nullptr)
	{
		// Todo: Fix rotation
		creature->entity_data.head_rotation = rotationY;
		creature->entity_data.binary_toggles |= 1 << (int)cube::Enums::StateFlags::ActiveLantern;
	}

	return creature;
}*/

/*
* Spawns a fish at the given position. Any of the other parameters is -1, it means that it will be decided randomly.
* @param	{const LongVector3&}	position	The Position to spawn the fish at.
* @param	{int}					entityType	The type of the creature to spawn [0-12]. If -1, a random fish will be spawned.
* @param	{int}					level		The level of the creature to spawn. If -1, a random level will be assigned.
* @param	{int}					friendly	If the creature is friendly or not [0 = hostile, 1 = friendly]. If -1, it will be random.
*/
/*cube::Creature* SpawnFish(const LongVector3& position, int entityType = -1, int level = -1, int friendly = -1)
{

}*/

/*std::vector<cube::Creature*> SpawnFishes(int amount)
{
	const static long long SPAWN_RANGE = 2000000;

	if (amount < 0)
	{
		return;
	}

	std::vector<cube::Creature*> creatures;

	LongVector3 position = cube::GetGame()->GetPlayer()->entity_data.position;
	for (int i = 0; i < amount; i++)
	{
		LongVector3 offset = cube::CreatureFactory::GetRandomOffset(SPAWN_RANGE);
		offset.x += position.x;
		offset.y += position.y;
		offset.z += position.z;
		cube::Creature* creature = cube::CreatureFactory::SpawnFish(offset, -1, -1, 1);
		if (creature != nullptr)
		{
			creatures.push_back(creature);
		}
	}

	return creatures;
}*/

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
		if (swscanf_s(msg, L"/bit %d", &index) == 1)
		{
			bit = index;
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
			cube::CreatureFactory::SpawnChest(player->entity_data.position, player->entity_data.head_rotation, index, 4);
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