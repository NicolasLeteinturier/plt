#include "Movement.h"

using namespace state;

Movement::Movement()
{
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

	printf("Cette unité ne fait pas partie des unités à deplacer\n");

	return;
}

void Movement::MoveAllUnit()
{
	unsigned int n = units.size();
	for(unsigned int i = 0; i < n; i++)
	{
		destination->listUnit.push_back(units[0]);
		units.erase(units.begin());
	}

	printf("Les mouvements sont finis, toutes les unités ont atteint leurs destinations\n");

	return;
}

void Movement::StopMovement()
{
	unsigned int n = units.size();
	for(unsigned int i = 0; i < n; i++)
	{
		origin->listUnit.push_back(units[0]);
		units.erase(units.begin());
	}

	printf("Les mouvements sont arrêté, toutes les unités non déplacé sont revenu à leur pays d'origine\n");

	return;
}

void Movement::AddUnitToMove(std::shared_ptr<Unit> unit)
{
	for(unsigned int i = 0; i < origin->listUnit.size(); i++)
	{
		if(origin->listUnit[i] == unit)
		{
			units.push_back(unit);
			origin->listUnit.erase(origin->listUnit.begin() + i);
			return;
		}
	}

	return;
}

ActionType Movement::GetActionType()
{
	return(ActionType::_MOVEMENT);
}



