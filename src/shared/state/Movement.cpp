#include "Movement.h"

using namespace state;

Movement::Movement()
{
	return;
}

void Movement::MoveUnit(std::shared_ptr<Unit> unit)
{
	for(unsigned int i = 0; i < units.size(); i++)
	{
		if(units[i] == unit)
		{
			destination->listUnit.push_back(unit);
			units.erase(units.begin() + i);
			return;
		}
	}

	printf("Cette unité ne fait pas partie des unités à deplacer");

	return;
}

void Movement::MoveAllUnit()
{
	for(unsigned int i = 0; i < units.size(); i++)
	{
		destination->listUnit.push_back(units[i]);
		units.erase(units.begin() + i);
	}

	printf("Les mouvements sont finis, toutes les unités ont atteint leurs destinations");

	return;
}

void StopMovement()
{
	for(unsigned int i = 0; i < units.size(); i++)
	{
		origin->listUnit.push_back(units[i]);
		units.erase(units.begin() + i);
	}

	printf("Les mouvements sont arrêté, toutes les unités non déplacé sont revenu à leur pays d'origine");

	return;
}

ActionType Movement::GetActionType()
{
	return(ActionType::Movement);
}



