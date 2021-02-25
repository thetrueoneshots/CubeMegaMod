#include "main.h"
#include <stdlib.h>

#include "src/cwsdk-extension.h"

// Create global vars here
#include "src/hooks.h"

cube::Creature* SpawnCreature(const LongVector3& position, int entityType, int entityBehaviour, int level)
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

void SpawnChest(const LongVector3& position, float rotationY, int chestType, int level)
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
}

/*
* Spawns a fish at the given position. Any of the other parameters is -1, it means that it will be decided randomly.
* @param	{const LongVector3&}	position	The Position to spawn the fish at.
* @param	{int}					entityType	The type of the creature to spawn [0-12]. If -1, a random fish will be spawned.
* @param	{int}					level		The level of the creature to spawn. If -1, a random level will be assigned.
* @param	{int}					friendly	If the creature is friendly or not [0 = hostile, 1 = friendly]. If -1, it will be random.
*/
void SpawnFish(const LongVector3& position, int entityType = -1, int level = -1, int friendly = -1)
{
	const static int ENTITY_COUNT = 13;
	const static int MAX_LEVEL = 5;
	const static int ENTITY_TYPES[ENTITY_COUNT] = {
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

	// Todo: Fix randomness
	int random = std::rand();
	if (entityType == -1)
	{
		entityType = random % ENTITY_COUNT;
	}

	// Todo: Fix random leveling to spawn more lowered leveled ones
	if (level == -1)
	{
		level = random % MAX_LEVEL;
	}

	if (friendly == -1)
	{
		friendly = random % 2;
	}

	cube::Creature* creature = SpawnCreature(
		cube::GetGame()->GetPlayer()->entity_data.position,
		ENTITY_TYPES[entityType],
		(int)cube::Enums::EntityBehaviour::Hostile,
		level
	);

	if (creature != nullptr)
	{
		creature->entity_data.appearance.flags2 |= friendly << (int)cube::Enums::AppearanceModifiers::IsFriendly;
		
		// Todo: Only showing light sometimes
		for (int i = 0; i < 16; i++)
		{
			creature->entity_data.binary_toggles |= 1 << i;
		}

		creature->entity_data.HP = creature->GetMaxHP();
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

		cube::Creature* player = cube::GetGame()->GetPlayer();
		int index = 0;

		if (!wcscmp(msg, L"/fish") || swscanf_s(msg, L"/fish %d", &index) == 1)
		{
			if (index == 0)
			{
				index = 1;
			}
			
			for (int i = 0; i < index; i++)
			{
				SpawnFish(player->entity_data.position, -1, -1, 1);
			}
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
			
			SpawnChest(player->entity_data.position, player->entity_data.head_rotation, index, 4);
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