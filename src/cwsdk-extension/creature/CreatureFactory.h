#pragma once

#include "cwsdk.h"

namespace cube
{
	class Creature;

	class CreatureFactory
	{
	public:
		static long long GenerateId();

		static void SetAppearance(cube::Creature* creature, int entityType, int entityBehaviour, int level);

		static void AddCreatureToWorld(cube::Creature* creature);

		static cube::Creature* SpawnCreature(const LongVector3& position, int entityType, int entityBehaviour, int level);
		static cube::Creature* SpawnChest(const LongVector3& position, float rotationY, int chestType, int level);
		static cube::Creature* SpawnFish(const LongVector3& position, int entityType = -1, int level = -1, int friendly = -1);

		static std::vector<cube::Creature*> SpawnFishes(int amount, long long range = 2000000);

		static LongVector3 GetRandomOffset(long long range);
	};
}