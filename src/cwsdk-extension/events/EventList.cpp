#include "EventList.h"

cube::EventList::EventList()
{
}

cube::EventList::~EventList()
{
	for (cube::Event* e : events)
	{
		delete e;
	}
}

cube::Event* cube::EventList::Find(EventType type)
{
	for (cube::Event* e : events)
	{
		if (e->eventType == type)
		{
			return e;
		}
	}

	return nullptr;
}

void cube::EventList::Remove(EventType type)
{
	for (int i = 0; i < events.size(); i++)
	{
		cube::Event* e = events.at(i);
		if (e->eventType == type)
		{
			switch (e->eventType)
			{
			case EventType::AddGold:
				delete (cube::AddGoldEvent*)e;
				break;
			default:
				delete e;
				break;
			}
			
			events.erase(events.begin() + i);
			return;
		}
	}
}

void cube::EventList::Add(Event* e)
{
	if (e == nullptr)
	{
		return;
	}

	events.push_back(e);
}
