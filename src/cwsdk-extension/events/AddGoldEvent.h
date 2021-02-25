#pragma once

#include "cwsdk.h"

#include "Event.h"
#include "../Timer.h"

namespace cube
{
	class AddGoldEvent : public Event
	{
	private:
		Timer m_PrintTimer;
	public:
		AddGoldEvent();
		~AddGoldEvent();

		void Update() override;
	};
}