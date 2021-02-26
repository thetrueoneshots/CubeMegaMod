#include "HealAbility.h"

#include "cwsdk.h"

cube::HealAbility::HealAbility()
	: Ability()
{
}

cube::HealAbility::~HealAbility()
{
}

void cube::HealAbility::Execute(cube::Creature* player)
{
	const static auto COST = 50;
	if (player->entity_data.hit_combo < COST)
	{
		return;
	}

	player->entity_data.hit_combo -= COST;
	player->entity_data.HP = player->GetMaxHP();
}
