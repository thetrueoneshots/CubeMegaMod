#include "QuestMod.h"

#include "hooks/ChangeQuestItemName.h"
#include "hooks/ChangeQuestDescription.h"
#include <utility>
#include "../../cwsdk-extension.h"


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
	MemoryHelper::FindAndReplaceString(L"Formula: ", L"[Quest]: ");
	SetupOnGetItemName();
	SetupOnGetItemDescription();
}

void QuestMod::OnCreatureDeath(cube::Creature* creature, cube::Creature* attacker)
{
	cube::Creature* player = cube::GetGame()->GetPlayer();
	if (player->id == attacker->id)
	{
		auto ingredients = &player->inventory_tabs.at(cube::Inventory::IngredientsTab);

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
}
