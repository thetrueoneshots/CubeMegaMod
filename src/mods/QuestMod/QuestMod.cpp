#include "QuestMod.h"

#include "hooks/ChangeQuestItemName.h"

void QuestMod::OnGameTick(cube::Game* game)
{
	static bool init = false;
	if (!init)
	{
		init = true;
		game->speech.item_identifier_map.find(IntVector2(2, 0))->second = L"Quest: ";
	}
}

void QuestMod::Initialize()
{
	MemoryHelper::FindAndReplaceString(L"Formula: ", L"[Quest]: ");
	SetupOnGetItemName();
}
