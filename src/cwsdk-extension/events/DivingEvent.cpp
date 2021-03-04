#include "DivingEvent.h"

#include "../Inventory.h"
#include "../creature/CreatureFactory.h"
#include "../helper/Helper.h"

cube::DivingEvent::DivingEvent()
	: Event(), m_ItemEffectTimer(nullptr)
{
	eventType = cube::EventType::Diving;

	m_SpawnTimer = cube::Timer(FISH_SPAWN_INTERVAL, m_CurrentTime);
	m_TreasureTimer = cube::Timer(TREASURE_SPAWN_INTERVAL, m_CurrentTime);
	m_BoundsTimer = cube::Timer(BOUNDS_CHECK_INTERVAL, m_CurrentTime);

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
	HandleItemEffectTimer();

	// Spawn treasures
	HandleTreasureTimer();

	// Spawn fishes
	HandleFishTimer();

	// Check for fishes and treasures to be deleted
	HandleBoundsCheckTimer();
}

// Todo: Remove
void cube::DivingEvent::Initialize()
{
	s_Consumable = cube::Item(11, 36);
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

		// Reset to stamina loss underwater
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x5C);
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
	cube::Creature* player = cube::GetGame()->GetPlayer();
	if (player->gold >= 10)
	{
		player->gold -= 10;

		// Set timer
		m_ItemEffectTimer = new cube::Timer(10, m_CurrentTime);

		// Stamina gain underwater.
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x58);

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
	m_SpawnedCreatures.push_back({ position, creatures });
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
	LongVector3 offset = cube::CreatureFactory::GetRandomOffset(2 * CREATURE_SPAWN_RANGE);
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
		m_SpawnedTreasures.push_back(creature);
	}
}

/*
* Generates a chest type to spawn. Certain chests are more likely to spawn than others.
*/
int cube::DivingEvent::GenerateChestType()
{
	const static int NORMAL_CHANCE = 60;
	const static int SKULL_CHANCE = 20;
	const static int OBSEDIAN_CHANCE = 10;
	const static int BONE_CHANCE = 10;

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
	std::vector<int> toBeErased;
	for (int i = 0; i < m_SpawnedCreatures.size(); i++)
	{
		auto p = m_SpawnedCreatures.at(i);
		if (DistanceSquared(p.position, position) < dist)
		{
			continue;
		}

		for (auto c : p.creatures)
		{
			c->entity_data.HP = 0;
		}

		toBeErased.push_back(i);
	}

	int cnt = 0;
	for (auto i : toBeErased)
	{
		m_SpawnedCreatures.erase(m_SpawnedCreatures.begin() + i - cnt);
		cnt++;
	}
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
	const static auto distTreasure = (BOUNDS_CHECK_DIST_MULTIPLIER * 2 * CREATURE_SPAWN_RANGE) * (BOUNDS_CHECK_DIST_MULTIPLIER * 2 * CREATURE_SPAWN_RANGE);

	std::vector<int> toBeErased;
	for (int i = 0; i < m_SpawnedTreasures.size(); i++)
	{
		auto p = m_SpawnedTreasures.at(i);
		if (DistanceSquared(p->entity_data.position, position) < distTreasure)
		{
			continue;
		}

		p->entity_data.HP = 0;

		toBeErased.push_back(i);
	}

	int cnt = 0;
	for (auto i : toBeErased)
	{
		m_SpawnedTreasures.erase(m_SpawnedTreasures.begin() + i - cnt);
		cnt++;
	}
}
