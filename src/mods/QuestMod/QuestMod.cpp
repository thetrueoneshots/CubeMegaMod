#include "QuestMod.h"

#include "hooks/ChangeQuestItemName.h"
#include "hooks/ChangeQuestDescription.h"
#include <utility>
#include "../../cwsdk-extension.h"
#include <algorithm>
#include <map>


void QuestMod::OnGameTick(cube::Game* game)
{
	const static int ID_OFFSET = 15;
	static bool init = false;
	if (!init)
	{
		init = true;
		game->speech.item_identifier_map.insert_or_assign(std::make_pair<uint32_t,uint32_t>(1, ID_OFFSET), L"QuestKill");
		game->speech.item_identifier_map.insert_or_assign(std::make_pair<uint32_t, uint32_t>(1, ID_OFFSET + 1), L"QuestGather");
		game->speech.item_identifier_map.insert_or_assign(std::make_pair<uint32_t, uint32_t>(1, ID_OFFSET + 2), L"QuestDeliver");
		game->speech.item_identifier_map.insert_or_assign(std::make_pair<uint32_t, uint32_t>(1, ID_OFFSET + 3), L"QuestTalk");
	}
	
}

void QuestMod::Initialize()
{
	// Todo: patch length
	MemoryHelper::FindAndReplaceString(L"Formula: ", L"[Quest]: ");
	SetupOnGetItemName();
	SetupOnGetItemDescription();
}

void QuestMod::OnCreatureDeath(cube::Creature* creature, cube::Creature* attacker)
{
	//cube::Creature* player = cube::GetGame()->GetPlayer();
	
	cube::Creature* foundPlayer = nullptr;
	for (cube::Creature* c : cube::GetGame()->world->creatures)
	{
		if (c->entity_data.hostility_type == (int)cube::Enums::EntityBehaviour::Player)
		{
			if (c->id == attacker->id)
			{
				foundPlayer = c;
			}
			else if (c->pet_id == attacker->id)
			{
				foundPlayer = c;
			}
		}
	}

	if (foundPlayer == nullptr)
	{
		return;
	}
	
	if (foundPlayer->inventory_tabs.size() < cube::Inventory::IngredientsTab)
	{
		return;
	}

	auto ingredients = &foundPlayer->inventory_tabs.at(cube::Inventory::IngredientsTab);

	for (int i = ingredients->size() - 1; i >= 0 ; i--)
	{
		cube::ItemStack* stack = &ingredients->at(i);
		if (stack->item.category == 2)
		{
			cube::Quest* quest = (cube::Quest*)&stack->item;
			if (quest->GetType() == cube::Quest::QuestType::Killing)
			{
				if (quest->GetSubType() == creature->entity_data.race)
				{
					quest->IncreaseProgress();
					if (quest->IsCompleted())
					{
						quest->Complete();
						ingredients->erase(ingredients->begin() + i);
					}
				}
			}
		}
	}
}

int QuestMod::OnCreatureTalk(cube::Game* game, cube::Creature* creature)
{
	// Check if already talked to.
	if (std::find(m_TalkedIds.begin(), m_TalkedIds.end(), creature->id) != m_TalkedIds.end())
	{
		return 0;
	}
	// Pushing in front, to make the find return faster on the latest NPC's talked to.
	m_TalkedIds.push_front(creature->id);

	// Check elledgible to drop a quest.
	if (creature->id % 5 != 0)
	{
		return 0;
	}

	long long mod = std::abs(creature->id / 5);
	while (mod > INT_MAX)
	{
		mod = mod >> 2;
	}

	cube::Item item(2, 0);
	item.modifier = (mod / 4) * 4; // Make multiple of 4.
	item.rarity = mod % 5;
	cube::Creature* player = cube::GetGame()->GetPlayer();
	cube::Helper::DropItem(player, item, 1);

	return 0;
}
