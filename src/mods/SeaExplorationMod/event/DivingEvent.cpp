#include "DivingEvent.h"

const static bool DEBUG_DIVING_EVENT = false;

cube::DivingEvent::DivingEvent(bool* autoGoldUsage)
	: Event(), m_ItemEffectTimer(nullptr)
{
	this->autoGoldUsage = autoGoldUsage;
	eventType = cube::EventType::Diving;

	m_SpawnTimer = cube::Timer(FISH_SPAWN_INTERVAL, m_CurrentTime);
	m_TreasureTimer = cube::Timer(TREASURE_SPAWN_INTERVAL, m_CurrentTime);
	m_BossTimer = cube::Timer(BOSS_SPAWN_INTERVAL, m_CurrentTime);
	m_BoundsTimer = cube::Timer(BOUNDS_CHECK_INTERVAL, m_CurrentTime);

	SetDiving(true);
}

cube::DivingEvent::~DivingEvent()
{
	cube::Game* game = cube::GetGame();
	if (game == nullptr || game->host.running == false)
	{
		return;
	}

	auto map = &game->host.world.id_to_creature_map;
	auto list = &game->host.world.creatures;
	if (m_ItemEffectTimer != nullptr)
	{
		delete m_ItemEffectTimer;
	}

	for (auto p : m_SpawnedCreatures)
	{
		for (auto pair : p.creature_ids)
		{
			auto creature = map->find(pair.id);
			if (creature != map->end())
			{
				creature->second->entity_data.HP = 0;
				map->erase(pair.id);
			}
		}
	}

	for (auto pair : m_SpawnedTreasures)
	{
		auto creature = map->find(pair.id);
		if (creature != map->end())
		{
			creature->second->entity_data.HP = 0;
			map->erase(pair.id);
		}
	}

	for (auto pair : m_SpawnedBosses)
	{
		auto creature = map->find(pair.id);
		if (creature != map->end())
		{
			creature->second->entity_data.HP = 0;
			map->erase(pair.id);
		}
	}

	SetDiving(false);
}

/*
* Calculates the squared distance between two longvector3 points.
* 
* @param	{const LongVector3&}	p1	Point one.
* @param	{const LongVector3&}	p2	Point two.
* @return	{long long}					Distance between the two points.
*/
static long long DistanceSquared(const LongVector3& p1, const LongVector3& p2)
{
	auto diffx = (p2.x - p1.x);
	auto diffy = (p2.y - p1.y);
	auto diffz = (p2.z - p1.z);
	return diffx * diffx + diffy * diffy + diffz * diffz;
}

/*
* Is called every gametick to update the diving event.
* This includes handling all timers and their assigned actions.
* 
* @return	{void}
*/
void cube::DivingEvent::Update()
{
	Event::Update();

	// Check for consumables
	//HandleItemEffectTimer();

	// Spawn treasures
	HandleTreasureTimer();

	// Spawn fishes
	HandleFishTimer();

	// Spawn bosses
	HandleBossTimer();

	// Check for fishes and treasures to be deleted
	HandleBoundsCheckTimer();
	
	UpdateIds();
}

void cube::DivingEvent::UpdateIds()
{
	for (auto& p : m_SpawnedCreatures)
	{
		for (int i = 0; i < p.creature_ids.size(); i++)
		{
			p.creature_ids[i].id = cube::CreatureFactory::CheckAndUpdateID(p.creature_ids[i].id);
			if (p.creature_ids[i].id == -1)
			{
				p.creature_ids.erase(p.creature_ids.begin() + i);
				p.creature_ids[i].creature->entity_data.HP = 0;
				i--;
			}
		}
	}
	
}

void cube::DivingEvent::SetDiving(bool diving)
{
	if (diving)
	{
		// Stamina gain underwater.
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x58);
	}
	else
	{
		// Reset to stamina loss underwater
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x5C);
	}
}

/*
* Checks if the player still has the underwater breathing ability.
* If this is not the case, check if the player can gain the ability again.
* 
* @return	{void}
*/
void cube::DivingEvent::HandleItemEffectTimer()
{
	if (m_ItemEffectTimer != nullptr && m_ItemEffectTimer->IsTriggered(m_CurrentTime))
	{
		delete m_ItemEffectTimer;
		m_ItemEffectTimer = nullptr;

		SetDiving(false);
	}

	if (m_ItemEffectTimer == nullptr)
	{
		ConsumeItem();
	}
}

/*
* Checks if the player can gain the underwater breathing ability for a defined amount of time.
* 
* @return	{void}
*/
void cube::DivingEvent::ConsumeItem()
{
	if (autoGoldUsage && !*autoGoldUsage)
	{
		return;
	}

	cube::Creature* player = cube::GetGame()->GetPlayer();
	if (player->gold >= 10)
	{
		player->gold -= 10;

		// Set timer
		m_ItemEffectTimer = new cube::Timer(10, m_CurrentTime);

		cube::GetGame()->PrintMessage(L"[Consumed] ", 100, 255, 0);
		cube::GetGame()->PrintMessage(L"10 Gold\n");
	}
}

/*
* Handles the fish timer. If this timer is triggered, it will try to spawn fishes around the player.
* 
* @return	{void}
*/
void cube::DivingEvent::HandleFishTimer()
{
	LongVector3 pos = cube::GetGame()->GetPlayer()->entity_data.position;

	if (m_SpawnTimer.IsTriggered(m_CurrentTime) && m_SpawnedCreatures.size() < MAX_FISH_COUNT / FISH_SPAWN_AMOUNT)
	{
		SpawnFishes(pos);
	}
}


/*
* Spawns fishes around the player.
* 
* @param	{const LongVector3&}	position	Position of the player.
* @return	{void}
*/
void cube::DivingEvent::SpawnFishes(const LongVector3& position)
{
	std::vector<cube::Creature*> creatures = cube::CreatureFactory::SpawnFishes(FISH_SPAWN_AMOUNT, CREATURE_SPAWN_RANGE);

	std::vector<IdCreaturePair> ids;
	for (auto creature : creatures)
	{
		ids.push_back({ creature->id, creature });
	}
	m_SpawnedCreatures.push_back({ position, ids });
}

/*
* Handles the treasure timer. If this timer is triggered, spawn a treasure in the water.
* 
* @return	{void}
*/
void cube::DivingEvent::HandleTreasureTimer()
{
	if (m_TreasureTimer.IsTriggered(m_CurrentTime) && m_SpawnedTreasures.size() < MAX_TREASURE_COUNT)
	{
		LongVector3 pos = cube::GetGame()->GetPlayer()->entity_data.position;
		SpawnTreasures(pos);
	}
}

/*
* Spawns a treasure somewhere depending on the player position.
* 
* @param	{const LongVector3&}	position	Position of the player.
* @return	{void}
*/
void cube::DivingEvent::SpawnTreasures(const LongVector3& position)
{
	// Calculate spawn position
	long long distance = (2.f + 1.f * Helper::RandomZeroToOne()) * CREATURE_SPAWN_RANGE;
	LongVector3 offset = cube::CreatureFactory::GetRandomOffset(distance);
	offset.x += position.x;
	offset.y += position.y;
	offset.z = position.z - abs(offset.z);

	// Check if there is water in at the spawnposition
	if (!Helper::PositionContainsWater(offset))
	{
		return;
	}
	
	int type = GenerateChestType();
	cube::Creature* creature = cube::CreatureFactory::SpawnChest(
		offset, 
		cube::GetGame()->GetPlayer()->entity_data.current_region, 
		type
	);

	if (creature != nullptr)
	{
		m_SpawnedTreasures.push_back({ creature->id, creature });
		cube::GetGame()->PrintMessage(L"A treasure chest appeared!\n", 255, 165, 0);
	}
}

/*
* Generates a chest type to spawn. Certain chests are more likely to spawn than others.
*/
int cube::DivingEvent::GenerateChestType()
{
	const static int NORMAL_CHANCE = 70;
	const static int SKULL_CHANCE = 20;
	const static int OBSEDIAN_CHANCE = 5;
	const static int BONE_CHANCE = 5;

	int random = rand() % 100;

	if (random < NORMAL_CHANCE)
	{
		return 0;
	}
	else if (random - NORMAL_CHANCE < SKULL_CHANCE)
	{
		return 1;
	}
	else if (random - NORMAL_CHANCE - SKULL_CHANCE < OBSEDIAN_CHANCE)
	{
		return 2;
	}
	else
	{
		return 3;
	}

	return 0;
}

void cube::DivingEvent::HandleBossTimer()
{
	if (m_BossTimer.IsTriggered(m_CurrentTime) && m_SpawnedBosses.size() < MAX_BOSS_COUNT)
	{
		LongVector3 pos = cube::GetGame()->GetPlayer()->entity_data.position;
		SpawnBoss(pos);
	}
}

void cube::DivingEvent::SpawnBoss(const LongVector3& position)
{
	long long distance = (2.f + 1.f * Helper::RandomZeroToOne()) * CREATURE_SPAWN_RANGE;
	LongVector3 offset = cube::CreatureFactory::GetRandomOffset(distance);
	offset.x += position.x;
	offset.y += position.y;
	offset.z = position.z - abs(offset.z);

	if (Helper::PositionContainsWater(offset))
	{
		cube::Creature* boss = cube::CreatureFactory::SpawnBoss(offset, cube::GetGame()->GetPlayer()->entity_data.current_region);
		if (boss != nullptr)
		{
			m_SpawnedBosses.push_back({ boss->id, boss });
			cube::GetGame()->PrintMessage(L"An underwater boss appeared!\n", 255, 165, 0);
		}
	}
}

/*
* Handles the boundscheck timer. If this timer is triggered, it will remove all the treasures and fishes
* that are out of range of the player.
* This is done so that the amount of added creatures to the game stays minimal.
* 
* @return	{void}
*/
void cube::DivingEvent::HandleBoundsCheckTimer()
{
	if (m_BoundsTimer.IsTriggered(m_CurrentTime))
	{
		LongVector3 pos = cube::GetGame()->GetPlayer()->entity_data.position;
		BoundCheckFishes(pos);
		BoundCheckTreasures(pos);
		BoundCheckBosses(pos);
	}
}

/*
* Checks if any spawned fishes are out of range of the player.
* If this is the case, said fishes are deleted.
* 
* @param	{const LongVector3&}	position	Position of the Player.
* @return	{void}
*/
void cube::DivingEvent::BoundCheckFishes(const LongVector3& position)
{
	const static auto dist = (BOUNDS_CHECK_DIST_MULTIPLIER * CREATURE_SPAWN_RANGE) * (BOUNDS_CHECK_DIST_MULTIPLIER * CREATURE_SPAWN_RANGE);
	auto map = &cube::GetGame()->host.world.id_to_creature_map;
	std::vector<int> toBeErased;
	for (int i = 0; i < m_SpawnedCreatures.size(); i++)
	{
		auto p = m_SpawnedCreatures.at(i);
		if (DistanceSquared(p.position, position) < dist)
		{
			continue;
		}

		for (auto pair : p.creature_ids)
		{
			
			auto creature = map->find(pair.id);
			if (creature != map->end())
			{
				creature->second->entity_data.HP = 0;
				map->erase(pair.id);
			}
		}

		toBeErased.push_back(i);
	}

	if (DEBUG_DIVING_EVENT && toBeErased.size() > 0)
	{
		wchar_t buffer[250];
		swprintf_s(buffer, 250, L"[Deleted fish cluster] %d\n", toBeErased.size());
		cube::GetGame()->PrintMessage(buffer, 255, 100, 175);
	}

	for (int i = toBeErased.size() - 1; i >= 0; i--)
	{
		m_SpawnedCreatures.erase(m_SpawnedCreatures.begin() + toBeErased.at(i));
	}

	/*int cnt = 0;
	for (auto i : toBeErased)
	{
		m_SpawnedCreatures.erase(m_SpawnedCreatures.begin() + i - cnt);
		cnt++;
	}*/
}

/*
* Checks if any spawned treasures are out of range of the player.
* If this is the case, said treasures are deleted.
*
* @param	{const LongVector3&}	position	Position of the Player.
* @return	{void}
*/
void cube::DivingEvent::BoundCheckTreasures(const LongVector3& position)
{
	const static auto distTreasure = (BOUNDS_CHECK_DIST_MULTIPLIER * 3 * CREATURE_SPAWN_RANGE) * (BOUNDS_CHECK_DIST_MULTIPLIER * 3 * CREATURE_SPAWN_RANGE);
	auto map = &cube::GetGame()->host.world.id_to_creature_map;

	std::vector<int> toBeErased;
	for (int i = 0; i < m_SpawnedTreasures.size(); i++)
	{
		auto pair = m_SpawnedTreasures.at(i);
		auto creature = map->find(pair.id);
		if (creature != map->end())
		{
			if (DistanceSquared(creature->second->entity_data.position, position) < distTreasure)
			{
				continue;
			}
			creature->second->entity_data.HP = 0;
			map->erase(pair.id);

			toBeErased.push_back(i);
		}
		else
		{
			toBeErased.push_back(i);
		}

		
	}

	if (DEBUG_DIVING_EVENT && toBeErased.size() > 0)
	{
		wchar_t buffer[250];
		swprintf_s(buffer, 250, L"[Deleted treasure] %d\n", toBeErased.size());
		cube::GetGame()->PrintMessage(buffer, 255, 100, 175);
	}

	int cnt = 0;
	for (auto i : toBeErased)
	{
		m_SpawnedTreasures.erase(m_SpawnedTreasures.begin() + i - cnt);
		cnt++;
	}
}

void cube::DivingEvent::BoundCheckBosses(const LongVector3& position)
{
	const static auto distBoss = (BOUNDS_CHECK_DIST_MULTIPLIER * 3 * CREATURE_SPAWN_RANGE) * (BOUNDS_CHECK_DIST_MULTIPLIER * 3 * CREATURE_SPAWN_RANGE);
	auto map = &cube::GetGame()->host.world.id_to_creature_map;

	std::vector<int> toBeErased;
	for (int i = 0; i < m_SpawnedBosses.size(); i++)
	{
		auto pair = m_SpawnedBosses.at(i);

		auto creature = map->find(pair.id);
		if (creature != map->end())
		{
			auto p = creature->second;
			if (p->entity_data.HP <= 0.f)
			{
				toBeErased.push_back(i);
				map->erase(p->id);
				continue;
			}

			if (cube::GetGame()->host.world.id_to_creature_map.find(p->id)->second != p)
			{
				toBeErased.push_back(i);
				continue;
			}

			bool found = false;
			std::list<cube::Creature*>* creatures = &cube::GetGame()->host.world.creatures;
			for (auto c : *creatures)
			{
				if (c->id == p->id)
				{
					found = true;
				}
			}

			if (!found)
			{
				map->erase(p->id);
				toBeErased.push_back(i);
				continue;
			}

			if (DistanceSquared(p->entity_data.position, position) < distBoss)
			{
				continue;
			}

			map->erase(p->id);
			p->entity_data.HP = 0;

			toBeErased.push_back(i);
		}
		else
		{
			toBeErased.push_back(i);
		}
		
	}

	if (DEBUG_DIVING_EVENT && toBeErased.size() > 0)
	{
		wchar_t buffer[250];
		swprintf_s(buffer, 250, L"[Deleted boss] %d\n", toBeErased.size());
		cube::GetGame()->PrintMessage(buffer, 255, 100, 175);
	}

	int cnt = 0;
	for (auto i : toBeErased)
	{
		m_SpawnedBosses.erase(m_SpawnedBosses.begin() + i - cnt);
		cnt++;
	}
}
