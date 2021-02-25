#include "CreatureFactory.h"

#include "cwsdk.h"

cube::Creature* cube::CreatureFactory::CreateCreature(CreatureType type, int star)
{
	cube::Game* game = cube::GetGame();
	long long id = 999 + game->host.world.id_to_creature_map.size();
	
	cube::Creature* creature = cube::Creature::Create(id);
	if (creature == nullptr)
	{
		return nullptr;
	}
	creature->entity_data.level = star;

	return creature;
}

void cube::CreatureFactory::AddCreatureToWorld(cube::Creature* creature)
{
	cube::Game* game = cube::GetGame();
	game->host.world.creatures.push_back(creature);
	game->host.world.id_to_creature_map.insert_or_assign(creature->id, creature);
}
