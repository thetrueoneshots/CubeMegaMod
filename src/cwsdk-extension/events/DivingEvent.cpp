#include "DivingEvent.h"

#include "../Inventory.h"

cube::DivingEvent::DivingEvent()
	: Event(), m_ItemEffectTimer(nullptr)
{
	eventType = cube::EventType::Diving;

	cube::GetGame()->PrintMessage(L"[Event Started] ", 100, 100, 255);
	cube::GetGame()->PrintMessage(L"Diving Event\n");

}

cube::DivingEvent::~DivingEvent()
{
	if (m_ItemEffectTimer != nullptr)
	{
		delete m_ItemEffectTimer;
	}

	cube::GetGame()->PrintMessage(L"[Event Ended] ", 100, 100, 255);
	cube::GetGame()->PrintMessage(L"Diving Event\n");
}

void cube::DivingEvent::Update()
{
	Event::Update();

	if (m_ItemEffectTimer != nullptr && m_ItemEffectTimer->IsTriggered(m_CurrentTime))
	{
		delete m_ItemEffectTimer;
		m_ItemEffectTimer = nullptr;

		// WriteByte reset
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x5C);
		cube::GetGame()->PrintMessage(L"[Effect Ended] ", 0, 100, 255);
		cube::GetGame()->PrintMessage(L"Dragon Root\n");
	}

	if (m_ItemEffectTimer == nullptr)
	{
		ConsumeItem();
	}
	
}

void cube::DivingEvent::Initialize()
{
	s_Consumable = cube::Item(11, 36);
}

void cube::DivingEvent::ConsumeItem()
{
	if (cube::Inventory::ConsumeItem(s_Consumable))
	{
		m_ItemEffectTimer = new cube::Timer(10, m_CurrentTime);
		WriteByte((char*)CWBase() + 0x2E038D + 0x02, 0x58);
		cube::GetGame()->PrintMessage(L"[Consumed] ", 100, 255, 0);
		cube::GetGame()->PrintMessage(L"Dragon Root\n");
	}
}
