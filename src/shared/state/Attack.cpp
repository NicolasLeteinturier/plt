#include "Attack.h"

using namespace state;

Attack::Attack()
{
}

void Attack::AddUnit(std::shared_ptr<Unit> unit)
{
	for(unsigned int i = 0; i < attackerCountry->listUnit.size(); i++)
	{
		if(attackerCountry->listUnit[i] == unit)
		{
			attackerUnits.push_back(unit);		//On rajoute l'unité à la liste des unités de l'attaquant
			attackerCountry->listUnit.erase(attackerCountry->listUnit.begin() + i);			//On efface cette même unité des unités disponible dans le pays (elle sera remise à la fin si elle a survecu)
			return;
		}
	}

	for(unsigned int i = 0; i < defencerCountry->listUnit.size(); i++)
	{
		if(defencerCountry->listUnit[i] == unit)
		{
			defencerUnits.push_back(unit);		//On rajoute l'unité à la liste des unités du defenseur
			defencerCountry->listUnit.erase(defencerCountry->listUnit.begin() + i);
			return;
		}
	}

	printf("Cette unité n'appartient ni au pays attaquant, ni au pays attaqué, elle n'a pas été ajouté");
	return;

}

void Attack::KillUnit(std::shared_ptr<Unit> unit)
{
	for(unsigned int i = 0; i < defencerUnits.size(); i++)
	{
		if(defencerUnits[i] == unit)
		{
			defencerUnits.erase(defencerUnits.begin() + i);
			return;
		}
	}

	for(unsigned int i = 0; i < attackerUnits.size(); i++)
	{
		if(attackerUnits[i] == unit)
		{
			attackerUnits.erase(attackerUnits.begin() + i);
			return;
		}
	}

	printf("Cette unité n'a pas été trouvé dans la bataille, peut-être est-elle déjà morte ?");

	return;

}

void Attack::AttackIsOver()
{
	for(unsigned int i = 0; i < defencerUnits.size(); i++)
	{
		defencerCountry->listUnit.push_back(defencerUnits[i]);
		defencerUnits.erase(defencerUnits.begin() + i);
	}

	for(unsigned int i = 0; i < attackerUnits.size(); i++)
	{
		attackerCountry->listUnit.push_back(attackerUnits[i]);
		attackerUnits.erase(attackerUnits.begin() + i);
	}

	printf("'attaque est fini, toutes les unités survivantes on été remise dans leur pays d'origine");

	return;
}

ActionType Attack::GetActionType()
{
	return(ActionType::_ATTACK);
}






