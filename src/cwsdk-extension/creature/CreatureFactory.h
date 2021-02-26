#pragma once

#include "cwsdk.h"

const static long long VISION_RANGE = 2000000;

namespace cube
{
	class Creature;

	class CreatureFactory
	{
	public:
		static long long GenerateId();

		static void SetAppearance(cube::Creature* creature, int entityType, int entityBehaviour, int level);

		static void AddCreatureToWorld(cube::Creature* creature);

		static cube::Creature* SpawnCreature(const LongVector3& position, const IntVector2& region, int entityType, int entityBehaviour, int level);
		static cube::Creature* SpawnChest(const LongVector3& position, const IntVector2& region, int chestType, int level = -1);
		static cube::Creature* SpawnFish(const LongVector3& position, const IntVector2& region, int entityType = -1, int level = -1, int friendly = -1);

		static std::vector<cube::Creature*> SpawnFishes(int amount, long long range = VISION_RANGE);

		static LongVector3 GetRandomOffset(long long range = VISION_RANGE);
	};
}