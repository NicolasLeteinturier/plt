#include "GameState.h"

using namespace state;

GameState::GameState()
{
	phase = initialisation;
	return;
}

void GameState::AddPlayer(std::shared_ptr<Player> player)
{
	listPlayer.push_back(player);
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
