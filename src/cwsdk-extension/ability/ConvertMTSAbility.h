#pragma once

#include "cwsdk.h"

#include "Ability.h"

namespace cube
{
	class ConvertMTSAbility : public Ability
	{
	public:
		ConvertMTSAbility() : Ability() {}
		~ConvertMTSAbility() {}

		void Execute(cube::Creature* player) override {

			player->stamina += player->entity_data.MP;
			player->entity_data.MP = 0;
			if (player->stamina > 1.f)
			{
				player->stamina = 1.f;
			}
		}
	};
}