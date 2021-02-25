#include "AddGoldEvent.h"

cube::AddGoldEvent::AddGoldEvent()
	: Event()
{
	m_PrintTimer = Timer(1, m_CurrentTime);
	eventType = cube::EventType::AddGold;

	cube::GetGame()->PrintMessage(L"[Event Started] ", 100, 100, 255);
	cube::GetGame()->PrintMessage(L"AddGold Event\n");
}

cube::AddGoldEvent::~AddGoldEvent()
{
	cube::GetGame()->PrintMessage(L"[Event Ended] ", 100, 100, 255);
	cube::GetGame()->PrintMessage(L"AddGold Event\n");
}

void cube::AddGoldEvent::Update()
{
	Event::Update();

	if (m_PrintTimer.IsTriggered(m_CurrentTime))
	{
		cube::GetGame()->GetPlayer()->gold++;
	}
}
