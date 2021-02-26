#pragma once

namespace cube
{
	class Creature;
	class Ability
	{
	public:
		Ability();
		~Ability();

		virtual void Execute(cube::Creature* player);
		static void CWAbility(cube::Creature* player, int id);
		static void CWBuff(cube::Creature* player, int id, float duration);
	};
}