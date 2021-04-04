#pragma once

#include "cwsdk.h"

namespace cube
{
	class Quest : public Item
	{
	public:
		enum class QuestType
		{
			Killing = 0,
			Gathering,
			Delivery,
			Talk,
			QuestType_END,
		};

		Quest() : Item(2, 0) {} 
		~Quest() {}

		QuestType GetType();
		int GetSubType();
		int GetTarget();
		int GetProgress();
		bool IsCompleted();
		void Complete();

		void SetProgress(int progress);
		void IncreaseProgress(long long data = 0);

		std::wstring* GetQuestDescription(cube::Speech* speech, std::wstring* str);
	};
}