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
			attackerUnits.push_back(unit);
			attackerCountry->listUnit.erase(attackerCountry->listUnit.begin() + i);
			return;
		}
	}

	for(unsigned int i = 0; i < defencerCountry->listUnit.size(); i++)
	{
		if(defencerCountry->listUnit[i] == unit)
		{
			defencerUnits.push_back(unit);
			defencerCountry->listUnit.erase(defencerCountry->listUnit.begin() + i);
			return;
		}
	}

	printf("Cette unité n'appartient ni au pays attaquant, ni au pays attaqué, elle n'a pas été ajouté\n");
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

	printf("Cette unité n'a pas été trouvé dans la bataille, peut-être est-elle déjà morte ?\n");

	return;

}

void Attack::AttackIsOver()
{
	if(attackerUnits.size() == 0)
	{
		unsigned int n = defencerUnits.size();
		for(unsigned int i = 0; i < n; i++)
		{
			defencerCountry->listUnit.push_back(defencerUnits[0]);
			defencerUnits.erase(defencerUnits.begin());
		}

		printf("L'attaquant à perdu, les unités du defenseur restante ont été remises dans leur pays d'origine\n");

		return;
	}

	else if(defencerUnits.size() == 0)
	{
		unsigned int n = attackerUnits.size();
		for(unsigned int i = 0; i < n; i++)
		{
			defencerCountry->listUnit.push_back(attackerUnits[0]);
			attackerUnits.erase(attackerUnits.begin());
		}

		printf("Le defenseur à perdu, les unités de l'attaquant ont été mises dans le pays du defenseur\n");

		return;
	}

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

	printf("L'attaque est fini, toutes les unités survivantes on été remise dans leur pays d'origine\n");

	return;
}

ActionType Attack::GetActionType()
{
	return(ActionType::_ATTACK);
}






