#pragma once

#include "cwsdk.h"

namespace cube::Helper
{
	enum class ItemGenerationType
	{
		Artifact = 0,
		Pet,
		Gold,
		Gear,
		Consumable,
	};

	void AnnounceItem(cube::Game* game, cube::Item* item, unsigned int count, cube::Creature* creature);
	void LevelUp(cube::Creature* player);
	cube::Item GenerateItem(ItemGenerationType type, IntVector2 region = IntVector2(0, 0));
	void DropItem(cube::Creature* creature, const cube::Item& item, int amount = 1);
	void DropItem(cube::Creature* creature, ItemGenerationType type, int amount = 1);

	void LoreInteraction(cube::Creature* player, int percentage);

	bool PositionContainsWater(const LongVector3& position);

	inline static int RandomInt()
	{
		static long long count = 0;
		int random = rand();
		count += random;
		if (count >= INT_MAX)
		{
			count -= INT_MAX;
		}
		std::srand(random + count);
		return random;
	}
	
	inline static float RandomZeroToOne()
	{
		return (float)(RandomInt() / (float)(RAND_MAX));
	}
}