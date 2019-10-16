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

void Movement::StopMovement()
{
	for(unsigned int i = 0; i < units.size(); i++)
	{
		origin->listUnit.push_back(units[i]);
		units.erase(units.begin() + i);
	}

	printf("Les mouvements sont arrêté, toutes les unités non déplacé sont revenu à leur pays d'origine");

	return;
}

void Movement::AddUnitToMove(std::shared_ptr<Unit> unit)
{
	for(unsigned int i = 0; i < origin->listUnit.size(); i++)
	{
		if(origin->listUnit[i] == unit)
		{
			units.push_back(unit);		//On rajoute l'unité à la liste des unités de l'attaquant
			origin->listUnit.erase(origin->listUnit.begin() + i);			//On efface cette même unité des unités disponible dans le pays (elle sera remise à la fin si elle a survecu)
			return;
		}
	}

	printf("Cette unité n'appartient ni au pays attaquant, ni au pays attaqué, elle n'a pas été ajouté");
	return;
}

ActionType Movement::GetActionType()
{
	return(ActionType::_MOVEMENT);
}



