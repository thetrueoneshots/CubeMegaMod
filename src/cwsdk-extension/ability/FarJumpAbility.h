#pragma once

#include "Ability.h"

namespace cube
{
	class FarJumpAbility : public Ability
	{
	private:
		int m_Direction;
	public:
		FarJumpAbility(int direction = 0);
		~FarJumpAbility();

		void Execute(cube::Creature* player) override;
	};
}