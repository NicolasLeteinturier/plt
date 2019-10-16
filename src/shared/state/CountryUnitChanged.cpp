#include "CountryUnitChanged.h"

using namespace state;

CountryUnitChanged::CountryUnitChanged()
{
}

EventType CountryUnitChanged::GetEventType()
{
	return(EventType::COUNTRY_UNIT_CHANGED);
}
