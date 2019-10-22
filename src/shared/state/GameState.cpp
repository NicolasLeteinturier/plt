#include "GameState.h"
#include "Initialisation.h"
#include "../../define.h"

using namespace state;

GameState::GameState()
{
	std::shared_ptr<Initialisation> init = std::make_shared<Initialisation>();
	char country_name[NB_COUNTRY][40] = {COUNTRY_NAME};
	for(unsigned int i = 0; i < NB_COUNTRY; i++)
	{
		std::shared_ptr<Country> new_country = std::make_shared<Country>();
		new_country->id = country_name[i];
		AddCountry(new_country);
		init->unattributedCountry.push_back(new_country);
	}
	currentAction = init;
	return;
}

void GameState::AddPlayer(std::shared_ptr<Player> player)
{
	if(currentAction->GetActionType() == ActionType::_INITIALISATION)
	{
		listPlayer.push_back(player);
	}
	else
	{
		printf("impossible d'ajouter un joueur, la partie a déjà commencé !");
	}
	return;
}

void GameState::DeletePlayer(std::shared_ptr<Player> player)
{
	for(unsigned int i = 0; i < listPlayer.size(); i++)
	{
		if(listPlayer[i] == player)
		{
			listPlayer.erase(listPlayer.begin() + i);
		}
	}
}

void GameState::AddCountry(std::shared_ptr<Country> country)
{
	listCountry.push_back(country);
	return;
}
