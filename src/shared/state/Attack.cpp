#include "Attack.h"

using namespace state;

Attack::Attack(){
	return;
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
			attackerUnits.push_back(unit);
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
		}
	}

	for(unsigned int i = 0; i < attackerUnits.size(); i++)
	{
		if(attackerUnits[i] == unit)
		{
			attackerUnits.erase(attackerUnits.begin() + i);
		}
	}

	printf("Cette unité n'a pas été trouvé dans la bataille, peut-être est-elle déjà morte ?");

	return;

}


ActionType Attack::GetActionType()
{
	return(ActionType::Attack);
}





