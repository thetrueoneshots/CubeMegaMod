#pragma once

#include "cwsdk.h"
#include <utility>

#include "Event.h"
#include "../Timer.h"

static cube::Item s_Consumable(11, 36);

const static double SPAWN_RATE = 1;
const static auto DELETE_RANGE_MULTIPLIER = 2;
const static long long SPAWN_RANGE = 5000000;
const static auto SPAWN_AMOUNT = 4;
const static auto MAX_CREATURES = 150;

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
		std::vector<SpawnMoment> spawnedCreatures;
	public:
		DivingEvent();
		~DivingEvent();

		void Update() override;

		static void Initialize();
	private:
		void ConsumeItem();
	};
}