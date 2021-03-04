#pragma once

#include "cwsdk.h"
#include <utility>

#include "Event.h"
#include "../Timer.h"

static cube::Item s_Consumable(11, 36);

// Fish spawning constants
const static double FISH_SPAWN_INTERVAL = 1;
const static auto FISH_SPAWN_AMOUNT = 4;
const static auto MAX_FISH_COUNT = 100;

// Treasure spawning constants
const static double TREASURE_SPAWN_INTERVAL = 60;
const static auto MAX_TREASURE_COUNT = 5;

// Other constants
const static auto BOUNDS_CHECK_DIST_MULTIPLIER = 2;
const static long long CREATURE_SPAWN_RANGE = 5000000;
const static double BOUNDS_CHECK_INTERVAL = 5;

struct SpawnMoment
{
	LongVector3 position;
	std::vector<cube::Creature*> creatures;
};

namespace cube
{
	class DivingEvent : public Event
	{
	private:
		cube::Timer* m_ItemEffectTimer;

		cube::Timer m_SpawnTimer;
		cube::Timer m_TreasureTimer;
		cube::Timer m_BoundsTimer;

		std::vector<SpawnMoment> m_SpawnedCreatures;
		std::vector<cube::Creature*> m_SpawnedTreasures;

	public:
		DivingEvent();
		~DivingEvent();

		void Update() override;

		static void Initialize();
	private:
		// Consumtion logic
		void HandleItemEffectTimer();
		void ConsumeItem();

		// Fish logic
		void HandleFishTimer();
		void SpawnFishes(const LongVector3& position);

		// Treasure logic
		void HandleTreasureTimer();
		void SpawnTreasures(const LongVector3& position);

		// Deletion logic
		void HandleBoundsCheckTimer();
		void BoundCheckFishes(const LongVector3& position);
		void BoundCheckTreasures(const LongVector3& position);
	};
}