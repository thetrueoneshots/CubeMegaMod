#include "Quest.h"

cube::Quest::QuestType cube::Quest::GetType()
{
	const static int MAX_QUESTS = (int)QuestType::QuestType_END;
	if (MAX_QUESTS == 0)
	{
		return QuestType(0);
	}
	return QuestType(this->modifier % MAX_QUESTS);
}

int cube::Quest::GetSubType()
{
	int subtypes[] = {
		100,
		60,
		56,
		34
	};
	int cnt = sizeof(subtypes) / sizeof(*subtypes);
	return subtypes[this->modifier / (int)QuestType::QuestType_END % 4];
}

int cube::Quest::GetTarget()
{
	return (this->rarity + 1) * 10;
}

int cube::Quest::GetProgress()
{
	return this->num_spirits;
}

bool cube::Quest::IsCompleted()
{
	return this->GetProgress() >= this->GetTarget();
}

void cube::Quest::Complete()
{
	this->SetProgress(0);
	cube::GetGame()->PrintMessage(L"Completed quest!\n", 64, 255, 64);
	cube::GetGame()->GetPlayer()->gold += this->GetReward().amount;
}

void cube::Quest::SetProgress(int progress)
{
	this->num_spirits = std::min<int>(progress, CHAR_MAX);
}

void cube::Quest::IncreaseProgress(long long data)
{
	if (data != 0)
	{
		// Todo: Check data
	}
	this->num_spirits++;
}

cube::Quest::QuestReward cube::Quest::GetReward()
{
	return { (this->rarity + 1) * 100, cube::Quest::QuestRewardType::Gold };
}

std::wstring* cube::Quest::GetQuestDescription(cube::Speech* speech, std::wstring* str)
{
	switch (this->GetType())
	{
	case QuestType::Killing:
	{
		wchar_t buffer[250];
		std::wstring subtype;
		speech->GetRaceName(&subtype, this->GetSubType());
		std::wstring progress;
		this->GetQuestProgress(speech, &progress);
		int target = this->GetTarget();
		int reward = this->GetReward().amount;
		swprintf_s(buffer, 250, L"\nTarget: %d x %s.\n\nReward: %d gold.\n\n%s \n", target, subtype.c_str(), reward, progress.c_str());
		*str = std::wstring(buffer);
	}
		break;
	case QuestType::Delivery:
		break;
	case QuestType::Gathering:
		break;
	case QuestType::Talk:
		break;
	}
	return str;
}

std::wstring* cube::Quest::GetQuestProgress(cube::Speech* speech, std::wstring* str)
{
	wchar_t buffer[250];
	int progress = this->GetProgress();
	int target = this->GetTarget();

	std::wstring subtype;
	speech->GetRaceName(&subtype, this->GetSubType());
	swprintf_s(buffer, 250, L"Progress: %d/%d %s\n", progress, target, subtype.c_str());
	*str = std::wstring(buffer);
	return str;
}

std::wstring* cube::Quest::GetQuestName(cube::Speech* speech, std::wstring* str)
{
	switch (this->GetType())
	{
	case QuestType::Killing:
	{
		wchar_t buffer[250];
		std::wstring buffer2;
		swprintf_s(buffer, 250, L"%s killing quest\n", speech->GetRaceName(&buffer2, this->GetSubType()));
		*str = std::wstring(buffer);
	}
		break;
	default:
		break;
	}
	return str;
}


