#pragma once

#include "cwsdk.h"

#include "Event.h"
#include "../Timer.h"

static cube::Item s_Consumable(11, 36);

namespace cube
{
	class DivingEvent : public Event
	{
	private:
		cube::Timer* m_ItemEffectTimer;
	public:
		DivingEvent();
		~DivingEvent();

		void Update() override;

		static void Initialize();
	private:
		void ConsumeItem();
	};
}