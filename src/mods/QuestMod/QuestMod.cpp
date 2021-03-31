#include "QuestMod.h"

#include "hooks/ChangeQuestItemName.h"
#include <utility>


void QuestMod::OnGameTick(cube::Game* game)
{
	static bool init = false;
	if (!init)
	{
		init = true;
		game->speech.item_identifier_map.insert_or_assign(std::make_pair<uint32_t,uint32_t>(1, 15), L"QuestKill");
		game->speech.item_identifier_map.insert_or_assign(std::make_pair<uint32_t, uint32_t>(1, 16), L"QuestGather");
		game->speech.item_identifier_map.insert_or_assign(std::make_pair<uint32_t, uint32_t>(1, 17), L"QuestDeliver");
		game->speech.item_identifier_map.insert_or_assign(std::make_pair<uint32_t, uint32_t>(1, 18), L"QuestTalk");
	}
	
}

void QuestMod::Initialize()
{
	MemoryHelper::FindAndReplaceString(L"Formula: ", L"[Quest]: ");
	SetupOnGetItemName();
}
