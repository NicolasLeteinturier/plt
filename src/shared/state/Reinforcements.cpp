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
	srand (time(NULL));
	while(availableUnits.size() != 0)
	{
		PlaceUnit(availableUnits[rand()%availableUnits.size()], availableCountry[availableUnits.size()%availableCountry.size()]);
	}
	return;
}

ActionType Reinforcements::GetActionType()
{
	return(ActionType::_REINFORCEMENTS);
}



