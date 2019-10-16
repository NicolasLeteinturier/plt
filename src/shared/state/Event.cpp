#include "Event.h"

using namespace state;

Event::Event()
{
}

EventType Event::GetEventType()
{
	return(EventType::COUNTRY_UNIT_CHANGED);
}
