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
	return 10;
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
	cube::GetGame()->GetPlayer()->gold += 100;
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
	std::wstring str;
	cube::GetGame()->PrintMessage(this->GetQuestDescription(&cube::GetGame()->speech, &str)->c_str(), 64, 64, 64);
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
		int progress = this->GetProgress();
		int target = this->GetTarget();
		swprintf_s(buffer, 250, L"You killed %d/%d %s.\n", progress, target, subtype.c_str());
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


