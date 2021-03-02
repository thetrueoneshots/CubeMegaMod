#include "DivingEvent.h"

#include "../Inventory.h"
#include "../creature/CreatureFactory.h"

cube::DivingEvent::DivingEvent()
	: Event(), m_ItemEffectTimer(nullptr)
{
	eventType = cube::EventType::Diving;

	m_SpawnTimer = cube::Timer(SPAWN_RATE, m_CurrentTime);
	m_TreasureTimer = cube::Timer(TREASURE_TIME, m_CurrentTime);

	cube::GetGame()->PrintMessage(L"[Event Started] ", 100, 100, 255);
	cube::GetGame()->PrintMessage(L"Diving Event\n");

}

cube::DivingEvent::~DivingEvent()
{
	if (m_ItemEffectTimer != nullptr)
	{
		delete m_ItemEffectTimer;
	}

	for (auto p : m_SpawnedCreatures)
	{
		for (auto c : p.creatures)
		{
			c->entity_data.HP = 0;
		}
	}

	for (auto p : m_SpawnedTreasures)
	{
		p->entity_data.HP = 0;
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

	cube::Creature* player = cube::GetGame()->GetPlayer();
	LongVector3 pos = player->entity_data.position;

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

	// Spawn treasures
	if (m_TreasureTimer.IsTriggered(m_CurrentTime) && m_SpawnedTreasures.size() < MAX_TREASURES)
	{
		//cube::GetGame()->PrintMessage(L"[Spawning Treasure] \n", 255, 50, 255);
		LongVector3 offset = cube::CreatureFactory::GetRandomOffset(2 * SPAWN_RANGE);
		offset.x += pos.x;
		offset.y += pos.y;
		offset.z = pos.z - abs(offset.z);
		int random = rand() % 100;
		int chest = 0;
		const static int NORMAL_CHANCE = 60;
		const static int SKULL_CHANCE = 20;
		const static int OBSEDIAN_CHANCE = 10;
		const static int BONE_CHANCE = 10;

		if (random < NORMAL_CHANCE)
		{
			chest = 0;
		}
		else if (random - NORMAL_CHANCE < SKULL_CHANCE)
		{
			chest = 1;
		} 
		else if (random - NORMAL_CHANCE - SKULL_CHANCE < OBSEDIAN_CHANCE)
		{
			chest = 2;
		}
		else
		{
			chest = 3;
		}

		cube::Creature* creature = cube::CreatureFactory::SpawnChest(offset, player->entity_data.current_region, chest);
		if (creature != nullptr)
		{
			m_SpawnedTreasures.push_back(creature);
		}
	}

	// Check for treasures to be deleted
	const auto distTreasure = (DELETE_RANGE_MULTIPLIER * 2 * SPAWN_RANGE) * (DELETE_RANGE_MULTIPLIER * 2 * SPAWN_RANGE);
	std::vector<int> toBeErased;
	for (int i = 0; i < m_SpawnedTreasures.size(); i++)
	{
		auto p = m_SpawnedTreasures.at(i);
		if (DistanceSquared(p->entity_data.position, pos) < distTreasure)
		{
			continue;
		}

		p->entity_data.HP = 0;

		toBeErased.push_back(i);
	}

	if (toBeErased.size() >= 1)
	{
		wchar_t buffer[250];
		swprintf_s(buffer, 250, L"[Deleted treasures] %d\n", toBeErased.size());
		cube::GetGame()->PrintMessage(buffer, 250, 170, 200);
	}

	int cnt = 0;
	for (auto i : toBeErased)
	{
		m_SpawnedTreasures.erase(m_SpawnedTreasures.begin() + i - cnt);
		cnt++;
	}

	// Spawn fishes
	if (m_SpawnTimer.IsTriggered(m_CurrentTime) && m_SpawnedCreatures.size() < MAX_CREATURES / SPAWN_AMOUNT)
	{
		//cube::GetGame()->PrintMessage(L"[Spawning Fishes] \n", 100, 170, 30);
		std::vector<cube::Creature*> creatures = cube::CreatureFactory::SpawnFishes(SPAWN_AMOUNT, SPAWN_RANGE);

		m_SpawnedCreatures.push_back({pos, creatures });
	}

	// Check for fishes to be deleted
	const auto dist = (DELETE_RANGE_MULTIPLIER * SPAWN_RANGE) * (DELETE_RANGE_MULTIPLIER * SPAWN_RANGE);
	//std::vector<int> toBeErased;
	toBeErased.clear();
	for (int i = 0; i < m_SpawnedCreatures.size(); i++)
	{
		auto p = m_SpawnedCreatures.at(i);
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
		//cube::GetGame()->PrintMessage(buffer, 250, 170, 100);
	}

	cnt = 0;
	for (auto i : toBeErased)
	{
		m_SpawnedCreatures.erase(m_SpawnedCreatures.begin() + i - cnt);
		cnt++;
	}
}

void cube::DivingEvent::Initialize()
{
	s_Consumable = cube::Item(11, 36);
}

void cube::DivingEvent::ConsumeItem()
{
	cube::Creature* player = cube::GetGame()->GetPlayer();
	if (player->gold >= 0)
	{
		player->gold -= 10;
		m_ItemEffectTimer = new cube::Timer(10, m_CurrentTime);
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x58);
		cube::GetGame()->PrintMessage(L"[Consumed] ", 100, 255, 0);
		cube::GetGame()->PrintMessage(L"10 Gold\n");
	}
	/*
	if (cube::Inventory::ConsumeItem(s_Consumable))
	{
		m_ItemEffectTimer = new cube::Timer(10, m_CurrentTime);
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x58);
		cube::GetGame()->PrintMessage(L"[Consumed] ", 100, 255, 0);
		cube::GetGame()->PrintMessage(L"Dragon Root\n");
	}*/
}
