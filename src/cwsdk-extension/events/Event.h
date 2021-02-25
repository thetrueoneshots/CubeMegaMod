#pragma once
#include <time.h>

namespace cube
{
	enum EventType
	{
		None = 0,
		AddGold,
		Diving,
	};

	class Event
	{
	protected:
		time_t m_CurrentTime;
		time_t m_LastTime;
	public:
		EventType eventType;

		Event();
		~Event();

		virtual void Update();
	};
}