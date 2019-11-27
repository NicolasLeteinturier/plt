#include "GameState.h"
#include "Initialisation.h"
#include "../../define.h"
#include "Reinforcements.h"
#include "Attack.h"
#include "Movement.h"
#include <iostream>

using namespace state;

GameState::GameState()
{
	std::shared_ptr<Initialisation> init = std::make_shared<Initialisation>();
	char country_name[NB_COUNTRY][40] = {COUNTRY_NAME};
	int country_neighboor[NB_OF_NEIGHBOOR] = {COUNTRY_NEIGHBOOR};
	unsigned int country_nb_neighboor[NB_COUNTRY] = {COUNTRY_NB_OF_NEIGHBOOR};

	for(unsigned int i = 0; i < NB_COUNTRY; i++)
	{
		std::shared_ptr<Country> new_country = std::make_shared<Country>();
		new_country->id = country_name[i];
		listCountry.push_back(new_country);
	}

	unsigned int compteur_neighboor = 0;

	for(unsigned int i = 0; i < NB_COUNTRY; i++)
	{
		for(unsigned int j = 0; j < country_nb_neighboor[i]; j++)
		{
			listCountry[i]->AddNeighboor(listCountry[country_neighboor[compteur_neighboor]]);
			compteur_neighboor++;
		}
		init->unattributedCountry.push_back(listCountry[i]);
	}

	currentAction = init;
	return;
}

void GameState::AddPlayer(bool isAnIA, std::string id)
{
	if(currentAction->GetActionType() == ActionType::_INITIALISATION)
	{
		std::shared_ptr<Player> player = std::make_shared<Player>();
		player->isAnIA = isAnIA;
		player->id = id;
		player->color = listPlayer.size();
		listPlayer.push_back(player);
		std::shared_ptr<Initialisation> init = std::dynamic_pointer_cast<Initialisation>(currentAction);
		init->listPlayer.push_back(player);
		currentPlayer = player;
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

void GameState::ChangeCountryOwner(std::shared_ptr<Country> country, std::shared_ptr<Player> new_owner)
{
	if(country->owner == new_owner){return;}
	country->owner->DeleteOwnedCountry(country);
	if(country->owner->listOwnedCountry.size() == 0)
	{
		for(unsigned int i = 0; i < listPlayer.size(); i++)
		{
			if(country->owner == listPlayer[i])
			{
				listPlayer.erase(listPlayer.begin() + i);
			}
		}
	}
	country->owner = new_owner;
	new_owner->AddOwnedCountry(country);
}

void GameState::GoToNextAction()
{
	std::cout << currentPlayer->id;
	if(currentAction->GetActionType() == ActionType::_INITIALISATION)
	{
		std::cout << " en phase d'initialisation" << std::endl;
		srand (time(NULL));
		std::shared_ptr<Initialisation> init = std::dynamic_pointer_cast<Initialisation>(currentAction);
		init->EndInitialisation();
		std::shared_ptr<Reinforcements> reinforcement = std::make_shared<Reinforcements>();
		for(int i = 0; i < currentPlayer->ReinforcementNumber(); i++)
		{
			std::shared_ptr<Unit> unit = std::make_shared<Unit>();
			int type = rand()%3;
			if(type == 0){unit->type = Type::attaquant;}
			else if(type == 1){unit->type = Type::neutre;}
			else{unit->type = Type::defensif;}
			reinforcement->availableUnits.push_back(unit);
		}
		reinforcement->availableCountry = currentPlayer->listOwnedCountry;
		currentAction = reinforcement;
		return;
	}
	if(currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
	{	
		std::cout << " en phase de renfort" << std::endl;
		std::shared_ptr<Reinforcements> reinforcement = std::dynamic_pointer_cast<Reinforcements>(currentAction);
		reinforcement->EndReinforcements();

		std::shared_ptr<Attack> attack = std::make_shared<Attack>();
		currentAction = attack;
		return;
	}
	if(currentAction->GetActionType() == ActionType::_ATTACK)
	{
		std::cout << " en phase d'attaque" << std::endl;
		std::shared_ptr<Movement> movement = std::make_shared<Movement>();
		currentAction = movement;
		return;
	}
	if(currentAction->GetActionType() == ActionType::_MOVEMENT)
	{
		std::cout << " en phase de mouvement" << std::endl;
		std::shared_ptr<Reinforcements> reinforcement = std::make_shared<Reinforcements>();
		for (unsigned int i = 0; i < listPlayer.size(); i++)
		{
			if(listPlayer[i] == currentPlayer)
			{
				currentPlayer = listPlayer[(i+1)%listPlayer.size()];
				break;
			}
		}

		for(int i = 0; i < currentPlayer->ReinforcementNumber(); i++)
		{
			std::shared_ptr<Unit> unit = std::make_shared<Unit>();
			int type = rand()%3;
			if(type == 0){unit->type = Type::attaquant;}
			else if(type == 1){unit->type = Type::neutre;}
			else{unit->type = Type::defensif;}
			reinforcement->availableUnits.push_back(unit);
		}
		reinforcement->availableCountry = currentPlayer->listOwnedCountry;
		currentAction = reinforcement;
		return;
	}
	return;
}



