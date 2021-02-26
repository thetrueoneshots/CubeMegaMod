#include "Ability.h"

#include "cwsdk.h"

cube::Ability::Ability()
{
}

cube::Ability::~Ability()
{
}

void cube::Ability::Execute(cube::Creature* player)
{
}

void cube::Ability::CWAbility(cube::Creature* player, int id)
{
	player->entity_data.current_ability = id;
	player->entity_data.time_since_ability = 0;
}
