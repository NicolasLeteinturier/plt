#include <SFML/Graphics.hpp>
#include "Player.h"
#include <math.h>
#include "../../define.h"

using namespace state;

Player::Player()
{
}

int Player::ReinforcementNumber(){
	unsigned int nbre_unit = 0;
	for(unsigned int i = 0; i < listOwnedCountry.size(); i++)
	{
		nbre_unit = nbre_unit + listOwnedCountry[i]->listUnit.size();
	}
	if(nbre_unit == 0)
	{
		return listOwnedCountry.size()*4;
	}
	else
	{
		return floor(listOwnedCountry.size()/2);
	}
}


void Player::AddOwnedCountry(std::shared_ptr<Country> country)
{
	for (unsigned int i = 0; i < listOwnedCountry.size(); i++)
	{
		if(listOwnedCountry[i] == country){return;}
	}

	listOwnedCountry.push_back(country);
	return;
}

void Player::DeleteOwnedCountry(std::shared_ptr<Country> country)
{
	for (unsigned int i = 0; i < listOwnedCountry.size(); i++)
	{
		if(listOwnedCountry[i] == country)
		{
			listOwnedCountry.erase(listOwnedCountry.begin() + i);
			return;
		}
	}
	//printf("le pays n'appartient pas à ce joueur");
	return;
}










