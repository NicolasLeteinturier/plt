#include "Reinforcements.h"

using namespace state;

Reinforcements::Reinforcements()
{
}

void Reinforcements::PlaceUnit(std::shared_ptr<Unit> unit, std::shared_ptr<Country> country)
{
	country->listUnit.push_back(unit);
	for(unsigned int i = 0; i < availableUnits.size(); i++)
	{
		if(availableUnits[i] == unit)
		{
			availableUnits.erase(availableUnits.begin() + i);
		}
	}
}

void Reinforcements::EndReinforcements()
{
	unsigned int compteur = 0;
	while(availableUnits.size() != 0)
	{
		PlaceUnit(availableUnits[0], availableCountry[compteur%availableCountry.size()]);
		compteur++;
	}
	return;
}

ActionType Reinforcements::GetActionType()
{
	return(ActionType::_REINFORCEMENTS);
}



