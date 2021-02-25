#include "Event.h"

#include "cwsdk.h"

cube::Event::Event()
{
	m_CurrentTime = time(NULL);
	eventType = EventType::None;
}

cube::Event::~Event()
{
}

void cube::Event::Update()
{
	m_LastTime = m_CurrentTime;
	m_CurrentTime = time(NULL);
}
