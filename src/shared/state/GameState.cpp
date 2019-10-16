#include "GameState.h"
#include "Initialisation.h"

using namespace state;

unsigned int nbre_pays = 17;

GameState::GameState()
{
	std::shared_ptr<Initialisation> init = std::make_shared<Initialisation>();
	for(unsigned int i = 0; i < nbre_pays; i++)
	{
		std::shared_ptr<Country> new_country = std::make_shared<Country>();
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
