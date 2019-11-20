#include "Reinforcements.h"

using namespace state;

Reinforcements::Reinforcements()
{
}

void Reinforcements::PlaceUnit(std::shared_ptr<Unit> unit, std::shared_ptr<Country> country)
{
	for(unsigned int i = 0; i < selectedUnits.size(); i++)
	{
		if(selectedUnits[i] == unit)
		{
			country->AddUnit(unit);
			selectedUnits.erase(selectedUnits.begin() + i);
			return;
		}
	}
}

void Reinforcements::EndReinforcements()
{
	srand (time(NULL));
	unsigned int n = availableUnits.size();
	for(unsigned int i = 0; i < n; i++)
	{
		selectedUnits.push_back(availableUnits[0]);
		availableUnits.erase(availableUnits.begin());
	}
	while(selectedUnits.size() != 0)
	{
		PlaceUnit(selectedUnits[rand()%selectedUnits.size()], availableCountry[rand()%availableCountry.size()]);
	}
	return;
}

ActionType Reinforcements::GetActionType()
{
	return(ActionType::_REINFORCEMENTS);
}



