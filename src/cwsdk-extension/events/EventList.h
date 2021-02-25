#pragma once
#include <vector>
#include <typeinfo>

#include "Event.h"
#include "AddGoldEvent.h"
#include "DivingEvent.h"

namespace cube
{

	class EventList {
	public:
		std::vector<cube::Event*> events;

		EventList();
		~EventList();

		cube::Event* Find(EventType type);
		void Remove(EventType type);
		void Add(cube::Event* e);
	};
}