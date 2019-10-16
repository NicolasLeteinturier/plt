#include "CountryOwnerChanged.h"

using namespace state;

CountryOwnerChanged::CountryOwnerChanged()
{
}

EventType CountryOwnerChanged::GetEventType()
{
	return(EventType::COUNTRY_OWNER_CHANGED);
}
