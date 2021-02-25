#pragma once

namespace cube
{
	class Creature;

	class CreatureFactory
	{
	public:
		static long long GenerateId();
		static void SetAppearance(cube::Creature* creature, int entityType, int entityBehaviour, int level);
		static void AddCreatureToWorld(cube::Creature* creature);
	};
}