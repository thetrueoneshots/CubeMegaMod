#include "CreatureFactory.h"

#include <random>
#include "time.h"
#include "cwsdk.h"

#include "Creature.h"
#include "../helper/Helper.h"

long long cube::CreatureFactory::GenerateId()
{
	cube::Game* game = cube::GetGame();
	//return 999 + game->host.world.creatures.size();

	const auto& map = game->host.world.id_to_creature_map;
	long long cnt = 1000;
	while (true) {
		if (map.find(cnt) == map.end())
		{
			return cnt;
		}

		if (cnt > 100000)
		{
			return -1;
		}
		cnt++;
	}
	
}

void cube::CreatureFactory::SetAppearance(cube::Creature* creature, int entityType, int entityBehaviour, int level)
{
	creature->entity_data.race = entityType;
	creature->entity_data.hostility_type = entityBehaviour;
	creature->entity_data.level = level;
	((void (*)(cube::World*, int, cube::Creature*))CWOffset(0x2B67B0))(&cube::GetGame()->host.world, 0, creature);
}

void cube::CreatureFactory::AddCreatureToWorld(cube::Creature* creature)
{
	cube::Game* game = cube::GetGame();
	game->host.world.creatures.push_back(creature);
	game->host.world.id_to_creature_map.insert_or_assign(creature->id, creature);
}

cube::Creature* cube::CreatureFactory::SpawnCreature(const LongVector3& position, const IntVector2& region, int entityType, int entityBehaviour, int level)
{
	cube::Creature* creature = cube::Creature::Create(cube::CreatureFactory::GenerateId());
	if (creature != nullptr)
	{
		creature->entity_data.position = position;
		creature->entity_data.current_region = region;
		creature->entity_data.yaw = Helper::RandomZeroToOne() * 360;
		cube::CreatureFactory::SetAppearance(creature, entityType, entityBehaviour, level);
		cube::CreatureFactory::AddCreatureToWorld(creature);
	}
	return creature;
}

cube::Creature* cube::CreatureFactory::SpawnChest(const LongVector3& position, const IntVector2& region, int chestType, int level)
{
	if (chestType < 0 || chestType >= 4)
	{
		return nullptr;
	}

	if (level < 0)
	{
		level = Helper::RandomZeroToOne() * 6;
	}

	cube::Creature* creature = SpawnCreature(position, region, 181 + chestType, (int)cube::Enums::EntityBehaviour::ExamineObject, level);
	if (creature != nullptr)
	{
		creature->entity_data.binary_toggles |= 1 << (int)cube::Enums::StateFlags::ActiveLantern;
		creature->entity_data.binary_toggles |= 1 << (int)cube::Enums::StateFlags::VisibleOnMap;
	}

	return creature;
}

/*
* Spawns a fish at the given position. Any of the other parameters is -1, it means that it will be decided randomly.
* @param	{const LongVector3&}	position	The Position to spawn the fish at.
* @param	{int}					entityType	The type of the creature to spawn [0-12]. If -1, a random fish will be spawned.
* @param	{int}					level		The level of the creature to spawn. If -1, a random level will be assigned.
* @param	{int}					friendly	If the creature is friendly or not [0 = hostile, 1 = friendly]. If -1, it will be random.
*/
cube::Creature* cube::CreatureFactory::SpawnFish(const LongVector3& position, const IntVector2& region, int entityType, int level, int friendly)
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
		position,
		region,
		ENTITY_TYPES[entityType],
		(int)cube::Enums::EntityBehaviour::Hostile,
		level
	);

	if (creature != nullptr)
	{
		creature->entity_data.appearance.flags2 |= friendly << (int)cube::Enums::AppearanceModifiers::IsFriendly;
		creature->entity_data.HP = creature->GetMaxHP();
	}

	return creature;
}

std::vector<cube::Creature*> cube::CreatureFactory::SpawnFishes(int amount, long long range)
{
	std::vector<cube::Creature*> creatures;

	if (amount <= 0)
	{
		return creatures;
	}

	cube::Creature* player = cube::GetGame()->GetPlayer();
	LongVector3 position = player->entity_data.position;
	for (int i = 0; i < amount; i++)
	{
		LongVector3 offset = cube::CreatureFactory::GetRandomOffset(range);
		offset.x += position.x;
		offset.y += position.y;
		offset.z += position.z;
		cube::Creature* creature = cube::CreatureFactory::SpawnFish(offset, player->entity_data.current_region, -1, -1, -1);
		if (creature != nullptr)
		{
			creatures.push_back(creature);
		}
	}

	return creatures;
}

LongVector3 cube::CreatureFactory::GetRandomOffset(long long range)
{
	//auto u = RandomZeroToOne() + RandomZeroToOne();
	auto t = Helper::RandomZeroToOne() * 2 * 3.14f;
	//auto r = u > 1.0f ? 2 - u : u;

	auto rr = range;
	auto cost = cos(t);
	auto sint = sin(t);
	return LongVector3(rr * cost, rr * sint, rr * cost * sint);
}
