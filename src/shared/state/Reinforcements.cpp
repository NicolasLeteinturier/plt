#include "Reinforcements.h"

using namespace state;

Reinforcements::Reinforcements()
{
	unsigned int nbre_renfort = availableCountry[0]->owner->ReinforcementNumber();
	for(unsigned int i = 0; i < nbre_renfort; i++)
	{
		
	}
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

ActionType Reinforcements::GetActionType()
{
	return(ActionType::_REINFORCEMENTS);
}



