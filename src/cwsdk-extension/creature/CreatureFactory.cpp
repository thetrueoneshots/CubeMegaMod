#include "CreatureFactory.h"

#include "cwsdk.h"

long long cube::CreatureFactory::GenerateId()
{
	cube::Game* game = cube::GetGame();
	return 999 + game->host.world.creatures.size();
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
