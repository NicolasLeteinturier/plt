#include "Initialisation.h"

using namespace state;

Initialisation::Initialisation(){
	return;
}

void Initialisation::AttributeCountry(std::shared_ptr<Country> country, std::shared_ptr<Player> player)
{
	country->owner = player;
	player->listOwnedCountry.push_back(country);
	for(unsigned int i = 0; i < unattributedCountry.size(); i++)
	{
		if(unattributedCountry[i] == country)
		{
			unattributedCountry.erase(unattributedCountry.begin() + i);
		}
	}
	return;
}

ActionType Initialisation::GetActionType()
{
	return(ActionType::_INITIALISATION);
}





