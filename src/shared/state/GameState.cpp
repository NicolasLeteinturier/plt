#include "GameState.h"
#include "Initialisation.h"
#include "../../define.h"
#include "Reinforcements.h"
#include "Attack.h"
#include "Movement.h"

using namespace state;

GameState::GameState()
{
	std::shared_ptr<Initialisation> init = std::make_shared<Initialisation>();
	char country_name[NB_COUNTRY][40] = {COUNTRY_NAME};
	for(unsigned int i = 0; i < NB_COUNTRY; i++)
	{
		std::shared_ptr<Country> new_country = std::make_shared<Country>();
		new_country->id = country_name[i];
		listCountry.push_back(new_country);
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
	if(currentAction->GetActionType() == ActionType::_INITIALISATION)
	{
		std::shared_ptr<Initialisation> init = std::dynamic_pointer_cast<Initialisation>(currentAction);
		init->EndInitialisation();
		std::shared_ptr<Reinforcements> reinforcement = std::make_shared<Reinforcements>();
		for(unsigned int i = 0; i < currentPlayer->ReinforcementNumber(); i++)
		{
			std::shared_ptr<Unit> unit = std::make_shared<Unit>();
			unit->type = Type::neutre;
			reinforcement->availableUnits.push_back(unit);
		}
		reinforcement->availableCountry = currentPlayer->listOwnedCountry;
		currentAction = reinforcement;
		return;
	}
	if(currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
	{
		std::shared_ptr<Reinforcements> reinforcement = std::dynamic_pointer_cast<Reinforcements>(currentAction);
		reinforcement->EndReinforcements();

		std::shared_ptr<Attack> attack = std::make_shared<Attack>();
		currentAction = attack;
		return;
	}
	if(currentAction->GetActionType() == ActionType::_ATTACK)
	{
		std::shared_ptr<Movement> movement = std::make_shared<Movement>();
		currentAction = movement;
		return;
	}
	if(currentAction->GetActionType() == ActionType::_MOVEMENT)
	{
		std::shared_ptr<Reinforcements> reinforcement = std::make_shared<Reinforcements>();
		for (int i = 0; i < listPlayer.size(); i++)
		{
			if(listPlayer[i] == currentPlayer)
			{
				currentPlayer = listPlayer[(i+1)%listPlayer.size()];
			}
		}

		for(int i = 0; i < currentPlayer->ReinforcementNumber(); i++)
		{
			std::shared_ptr<Unit> unit = std::make_shared<Unit>();
			unit->type = Type::defensif;
			reinforcement->availableUnits.push_back(unit);
		}
		reinforcement->availableCountry = currentPlayer->listOwnedCountry;
		currentAction = reinforcement;
		return;
	}
	return;
}



