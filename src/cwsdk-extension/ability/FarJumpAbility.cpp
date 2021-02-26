#include "FarJumpAbility.h"

#include "cwsdk.h"

cube::FarJumpAbility::FarJumpAbility(int direction)
{
	m_Direction = direction < 0 ? 0 : direction > 3 ? 3 : direction;
}

cube::FarJumpAbility::~FarJumpAbility()
{
}

void cube::FarJumpAbility::Execute(cube::Creature* player)
{
	const static auto COST = 0.75f;
	const static int IDS[4] =
	{
		77,
		78,
		79,
		116
	};

	if (player->stamina < COST)
	{
		return;
	}

	player->stamina -= COST;

	Ability::CWAbility(player, IDS[m_Direction]);
}
