#include "DivingEvent.h"

#include "../Inventory.h"
#include "../creature/CreatureFactory.h"

cube::DivingEvent::DivingEvent()
	: Event(), m_ItemEffectTimer(nullptr)
{
	eventType = cube::EventType::Diving;

	m_SpawnTimer = cube::Timer(SPAWN_RATE, m_CurrentTime);

	cube::GetGame()->PrintMessage(L"[Event Started] ", 100, 100, 255);
	cube::GetGame()->PrintMessage(L"Diving Event\n");

}

cube::DivingEvent::~DivingEvent()
{
	if (m_ItemEffectTimer != nullptr)
	{
		delete m_ItemEffectTimer;
	}


	for (auto p : spawnedCreatures)
	{
		for (auto c : p.creatures)
		{
			c->entity_data.HP = 0;
		}
	}

	cube::GetGame()->PrintMessage(L"[Event Ended] ", 100, 100, 255);
	cube::GetGame()->PrintMessage(L"Diving Event\n");
}

static long long DistanceSquared(const LongVector3& p1, const LongVector3& p2)
{
	auto diffx = (p2.x - p1.x);
	auto diffy = (p2.y - p1.y);
	auto diffz = (p2.z - p1.z);
	return diffx * diffx + diffy * diffy + diffz * diffz;
}

void cube::DivingEvent::Update()
{
	Event::Update();

	LongVector3 pos = cube::GetGame()->GetPlayer()->entity_data.position;

	// Check for consumables
	if (m_ItemEffectTimer != nullptr && m_ItemEffectTimer->IsTriggered(m_CurrentTime))
	{
		delete m_ItemEffectTimer;
		m_ItemEffectTimer = nullptr;

		// WriteByte reset
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x5C);
		cube::GetGame()->PrintMessage(L"[Effect Ended] ", 0, 100, 255);
		cube::GetGame()->PrintMessage(L"Dragon Root\n");
	}

	if (m_ItemEffectTimer == nullptr)
	{
		ConsumeItem();
	}


	// Spawn fishes
	if (m_SpawnTimer.IsTriggered(m_CurrentTime) && spawnedCreatures.size() < MAX_CREATURES / SPAWN_AMOUNT)
	{
		cube::GetGame()->PrintMessage(L"[Spawning Fishes] \n", 100, 170, 30);
		std::vector<cube::Creature*> creatures = cube::CreatureFactory::SpawnFishes(SPAWN_AMOUNT);

		spawnedCreatures.push_back({pos, creatures });
	}

	const auto dist = (DELETE_RANGE_MULTIPLIER * SPAWN_RANGE) * (DELETE_RANGE_MULTIPLIER * SPAWN_RANGE);
	std::vector<int> toBeErased;
	for (int i = 0; i < spawnedCreatures.size(); i++)
	{
		auto p = spawnedCreatures.at(i);
		if (DistanceSquared(p.position, pos) < dist)
		{
			continue;
		}

		for (auto c : p.creatures)
		{
			c->entity_data.HP = 0;
		}

		toBeErased.push_back(i);
	}

	if (toBeErased.size() >= 1)
	{
		wchar_t buffer[250];
		swprintf_s(buffer, 250, L"[Deleted Fishes] %d\n", toBeErased.size());
		cube::GetGame()->PrintMessage(buffer, 250, 170, 100);
	}

	int cnt = 0;
	for (auto i : toBeErased)
	{
		spawnedCreatures.erase(spawnedCreatures.begin() + i - cnt);
		cnt++;
	}
}

void cube::DivingEvent::Initialize()
{
	s_Consumable = cube::Item(11, 36);
}

void cube::DivingEvent::ConsumeItem()
{
	if (cube::Inventory::ConsumeItem(s_Consumable))
	{
		m_ItemEffectTimer = new cube::Timer(10, m_CurrentTime);
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x58);
		cube::GetGame()->PrintMessage(L"[Consumed] ", 100, 255, 0);
		cube::GetGame()->PrintMessage(L"Dragon Root\n");
	}
}
