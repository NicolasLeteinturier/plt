#include <queue>
#include <stack>
#include <thread>

/////////////////////////////////////////////////////////////////////////////////////////////////

// Generated by dia2code
#ifndef ENGINE__GAMEENGINE__H
#define ENGINE__GAMEENGINE__H

#include <memory>
#include <vector>

namespace state {
  class GameState;
};
namespace engine {
  class Command;
}

#include "../state/GameState.h"
#include "../state/Initialisation.h"
#include "Command.h"

namespace engine {

  /// class GameEngine - 
  class GameEngine {
    // Associations
    // Attributes
  public:
    std::shared_ptr<state::GameState> gameState;
    std::queue<std::shared_ptr<Command>> commands;
  private:
    std::stack<std::shared_ptr<state::GameState>> rollback;
    unsigned int etat;
    // Operations
  public:
    GameEngine ();
    void ExecuteCommands ();
    void Rollback ();
  private:
    void ExecuteAttackCommand ();
    void ExecuteMovementCommand ();
    void ExecuteReinforcementCommand ();
    void ExecuteInitialisationCommand ();
    int GetCountryClicked (int mousePositionX, int mousePositionY);
    void SaveGameState ();
    // Setters and Getters
  };

};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../define.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../state/Movement.h"
#include "../state/Attack.h"
#include "../state/Initialisation.h"
#include "../state/Reinforcements.h"
#include <algorithm>
#include <string>

using namespace engine;
using namespace state;

//unsigned int etat = 0;

GameEngine::GameEngine()
{
	etat = 0;
}

void GameEngine::Rollback()
{
	if(rollback.empty())
	{
		return;
	}
	//printf("dans le rollback\n");
	gameState = rollback.top();
	rollback.pop();
	return;
}

void GameEngine::ExecuteCommands()
{
	if(commands.empty())
	{
		return;
	}

	unsigned int n = commands.size();

	for(unsigned int i = 0; i < n; i++)
	{
		if(gameState->currentAction->GetActionType() == ActionType::_INITIALISATION)
		{
			ExecuteInitialisationCommand();
			commands.pop();
		}

		else if(gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
		{
			ExecuteReinforcementCommand();
			commands.pop();
		}

		else if(gameState->currentAction->GetActionType() == ActionType::_ATTACK)
		{
			ExecuteAttackCommand();
			commands.pop();
		}

		else if(gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
		{
			ExecuteMovementCommand();
			commands.pop();
		}
		//SaveGameState();
	}

	return;
}


void GameEngine::ExecuteAttackCommand()
{
	std::shared_ptr<Command> command = commands.front();
	std::shared_ptr<Country> selected_country = std::make_shared<Country>();

	if(command->pressedKey == KeyPressed::ESCAPE)
	{
		gameState->GoToNextAction();
		etat = 0;
	}

	// etat vaut 0 : selection du pays attaquant
	else if(etat == 0 && command->pressedKey == KeyPressed::LEFT_CLICK)
	{
		
		printf("ici avant seg fault 1\n");
		selected_country = command->countryClicked;
		if(selected_country->owner != gameState->currentPlayer)
		{
			printf("Ce pays ne vous appartient pas\n");
			return;
		}
		std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(gameState->currentAction);
		attack->attackerCountry = selected_country;
		etat = 1;
		return;
	}

	// etat vaut 1 : selection du pays à attaquer
	else if(etat == 1 && command->pressedKey == KeyPressed::LEFT_CLICK)
	{
		
		printf("ici avant seg fault 2\n");
		selected_country = command->countryClicked;
		if(selected_country->owner == gameState->currentPlayer)
		{
			printf("Vous ne pouvez pas vous attaquer vous même !!!\n");
			return;
		}
		std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(gameState->currentAction);

		unsigned int test = attack->attackerCountry->neighboor.size();

		// On verifie que le pays selectionné est bien voisin du pays de l'attaquant
		for(unsigned int i = 0; i < test; i++)
		{
			if(attack->attackerCountry->neighboor[i] == selected_country)
			{
				attack->defencerCountry = selected_country;
				attack->unitSelected = true;
				etat = 2;
				return;
			}
		}

		printf("Ce pays n'est pas voisin du vôtre\n");
	}

	// etat vaut 2 : l'attaquant selectionne les unités avec lesquelles il souhaite attaquer
	else if(etat == 2 && command->pressedKey == KeyPressed::LEFT_CLICK)
	{		
		printf("ici avant seg fault 3\n");
		std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(gameState->currentAction);

		if(command->unitClicked == UnitClickedType::DEF_PLUS)
		{
			// Si il ne reste qu'une unité dans le pays attaquant on ne l'ajoute pas aux unités attaquantes
			if(attack->attackerCountry->listUnit.size() <= 1)
			{
				printf("Vous ne pouvez pas vider entièrement vôtre pays\n");
				return;
			}

			for(unsigned int i = 0; i < attack->attackerCountry->listUnit.size(); i++)
			{
				if(attack->attackerCountry->listUnit[i]->type == Type::defensif)
				{
					attack->AddUnit(attack->attackerCountry->listUnit[i]);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::DEF_MOINS)
		{
			for(unsigned int i = 0; i < attack->attackerUnits.size(); i++)
			{
				if(attack->attackerUnits[i]->type == Type::defensif)
				{
					attack->attackerCountry->AddUnit(attack->attackerUnits[i]);
					attack->attackerUnits.erase(attack->attackerUnits.begin() + i);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::NEU_PLUS)
		{
			// Si il ne reste qu'une unité dans le pays attaquant on ne l'ajoute pas aux unités attaquantes
			if(attack->attackerCountry->listUnit.size() <= 1)
			{
				printf("Vous ne pouvez pas vider entièrement vôtre pays\n");
				return;
			}

			for(unsigned int i = 0; i < attack->attackerCountry->listUnit.size(); i++)
			{

				if(attack->attackerCountry->listUnit[i]->type == Type::neutre)
				{
					attack->AddUnit(attack->attackerCountry->listUnit[i]);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::NEU_MOINS)
		{
			for(unsigned int i = 0; i < attack->attackerUnits.size(); i++)
			{
				if(attack->attackerUnits[i]->type == Type::neutre)
				{
					attack->attackerCountry->AddUnit(attack->attackerUnits[i]);
					attack->attackerUnits.erase(attack->attackerUnits.begin() + i);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::ATT_PLUS)
		{
			// Si il ne reste qu'une unité dans le pays attaquant on ne l'ajoute pas aux unités attaquantes
			if(attack->attackerCountry->listUnit.size() <= 1)
			{
				printf("Vous ne pouvez pas vider entièrement vôtre pays\n");
				return;
			}

			for(unsigned int i = 0; i < attack->attackerCountry->listUnit.size(); i++)
			{
				if(attack->attackerCountry->listUnit[i]->type == Type::attaquant)
				{
					attack->AddUnit(attack->attackerCountry->listUnit[i]);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::ATT_MOINS)
		{
			for(unsigned int i = 0; i < attack->attackerUnits.size(); i++)
			{
				if(attack->attackerUnits[i]->type == Type::attaquant)
				{
					attack->attackerCountry->AddUnit(attack->attackerUnits[i]);
					attack->attackerUnits.erase(attack->attackerUnits.begin() + i);
					break;
				}
			}
			return;
		}

		else {return;}
		
	}

	// Si le joueur presse la touche entrée on passe à l'état suivant et on ajoute les unités du pays defenseur aux unités défensives
	else if(etat == 2 && command->pressedKey == KeyPressed::ENTER)
	{
		
		printf("ici avant seg fault 4\n");
		std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(gameState->currentAction);
		attack->unitSelected = false;

		unsigned int n = attack->defencerCountry->listUnit.size();
		//std::cout << "nombre d'unité pays attaqué = " << std::to_string(attack->defencerCountry->listUnit.size()) << std::endl;

		for(unsigned int i = 0; i < n; i++)
		{
			attack->AddUnit(attack->defencerCountry->listUnit[0]);
			//std::cout << "ajout d'une nouvelle unité à l'attaque" << std::endl;
		}
		attack->displayAttack = true;
		etat = 3;
	}

	// etat vaut 3 : on lance l'attaque ...
	else if(etat == 3 && command->pressedKey == KeyPressed::SPACE_BARRE)
	{
		
		printf("ici avant seg fault 5\n");
		std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(gameState->currentAction);

		if(attack->attackerUnits.size() == 0)
		{
			etat = 0;
			attack->displayAttack = false;
			attack->AttackIsOver();
			gameState->GoToNextAction();
			return;
		}

		if(attack->defencerUnits.size() == 0)
		{
			etat = 0;
			attack->displayAttack = false;
			attack->AttackIsOver();
			std::shared_ptr<Player> defencer = attack->defencerCountry->owner; 
			gameState->ChangeCountryOwner(attack->defencerCountry, attack->attackerCountry->owner);
			if(defencer->listOwnedCountry.size() == 0)
			{
				gameState->DeletePlayer(defencer);
			}
			gameState->GoToNextAction();
			return;
		}

		srand (time(NULL));

		int attacker_de = 0;
		int defencer_de = 0;

		while(attacker_de == defencer_de)
		{
			if(attack->attackerUnits[0]->type == Type::attaquant){attacker_de = rand()%8;}
			else if(attack->attackerUnits[0]->type == Type::defensif){attacker_de = rand()%4;}
			else if(attack->attackerUnits[0]->type == Type::neutre){attacker_de = rand()%6;}
			if(attack->defencerUnits[0]->type == Type::attaquant){defencer_de = rand()%4;}
			else if(attack->defencerUnits[0]->type == Type::defensif){defencer_de = rand()%8;}
			else if(attack->defencerUnits[0]->type == Type::neutre){defencer_de = rand()%6;}
		}

		if(attacker_de > defencer_de){attack->KillUnit(attack->defencerUnits[0]);}
		else if(attacker_de < defencer_de){attack->KillUnit(attack->attackerUnits[0]);}

		//std::cout << "score aux dés de l'attaquant = " << std::to_string(attacker_de) << std::endl;
		//std::cout << "score aux dés du defenceur = " << std::to_string(defencer_de) << std::endl;

		//std::cout << "nombre d'unité de l'attaquant = " << std::to_string((attack->attackerUnits.size())) << std::endl;
		//std::cout << "nombre d'unité du defenseur = " << std::to_string((attack->defencerUnits.size())) << std::endl;

	}

	return;

}


void GameEngine::ExecuteMovementCommand()
{
	std::shared_ptr<Command> command = commands.front();
	std::shared_ptr<Country> selected_country = std::make_shared<Country>();

	if(command->pressedKey == KeyPressed::ESCAPE)
	{
		gameState->GoToNextAction();
		etat = 0;
	}

	// etat vaut 0 : selection du pays d'origine
	else if(etat == 0 && command->pressedKey == KeyPressed::LEFT_CLICK)
	{
		
		printf("ici avant seg fault 6\n");
		selected_country = command->countryClicked;
		if(selected_country->owner != gameState->currentPlayer)
		{
			printf("ce pays ne vous appartient pas\n");
			return;
		}
		std::shared_ptr<Movement> movement = std::dynamic_pointer_cast<Movement>(gameState->currentAction);
		movement->origin = selected_country;
		etat = 1;
		return;
	}

	// etat vaut 1 : selection du pays de destination

	else if(etat == 1 && command->pressedKey == KeyPressed::LEFT_CLICK)
	{
		
		printf("ici avant seg fault 7\n");
		selected_country = command->countryClicked;
		std::cout << selected_country->owner->id << std::endl;
		if(selected_country->owner != gameState->currentPlayer)
		{
			printf("ce pays ne vous appartient pas\n");
			return;
		}
		std::shared_ptr<Movement> movement = std::dynamic_pointer_cast<Movement>(gameState->currentAction);
		movement->destination = selected_country;
		movement->unitSelected = true;
		etat = 2;
		return;
	}

	// etat vaut 2 : selection des unités à deplacer

	else if(etat == 2 && command->pressedKey == KeyPressed::LEFT_CLICK)
	{
		
		printf("ici avant seg fault 8\n");
		std::shared_ptr<Movement> movement = std::dynamic_pointer_cast<Movement>(gameState->currentAction);

		if(command->unitClicked == UnitClickedType::DEF_PLUS)
		{
			// Si il ne reste qu'une unité dans le pays d'origine on ne peut plus deplacer d'unité
			if(movement->origin->listUnit.size() <= 1)
			{
				printf("Vous ne pouvez pas vider entièrement vôtre pays\n");
				return;
			}

			for(unsigned int i = 0; i < movement->origin->listUnit.size(); i++)
			{
				if(movement->origin->listUnit[i]->type == Type::defensif)
				{
					movement->AddUnitToMove(movement->origin->listUnit[i]);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::DEF_MOINS)
		{
			for(unsigned int i = 0; i < movement->units.size(); i++)
			{
				if(movement->units[i]->type == Type::defensif)
				{
					movement->origin->AddUnit(movement->units[i]);
					movement->units.erase(movement->units.begin() + i);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::NEU_PLUS)
		{
			// Si il ne reste qu'une unité dans le pays d'origine on ne peut plus deplacer d'unité
			if(movement->origin->listUnit.size() <= 1)
			{
				printf("Vous ne pouvez pas vider entièrement vôtre pays\n");
				return;
			}

			for(unsigned int i = 0; i < movement->origin->listUnit.size(); i++)
			{
				if(movement->origin->listUnit[i]->type == Type::neutre)
				{
					movement->AddUnitToMove(movement->origin->listUnit[i]);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::NEU_MOINS)
		{
			for(unsigned int i = 0; i < movement->units.size(); i++)
			{
				if(movement->units[i]->type == Type::neutre)
				{
					movement->origin->AddUnit(movement->units[i]);
					movement->units.erase(movement->units.begin() + i);
					break;
				}
			}
			return;
		}
		
		else if(command->unitClicked == UnitClickedType::ATT_PLUS)
		{
			// Si il ne reste qu'une unité dans le pays d'origine on ne peut plus deplacer d'unité
			if(movement->origin->listUnit.size() <= 1)
			{
				printf("Vous ne pouvez pas vider entièrement vôtre pays\n");
				return;
			}

			for(unsigned int i = 0; i < movement->origin->listUnit.size(); i++)
			{
				if(movement->origin->listUnit[i]->type == Type::attaquant)
				{
					movement->AddUnitToMove(movement->origin->listUnit[i]);
					break;
				}
			}
			return;
		}

		else if(command->unitClicked == UnitClickedType::ATT_MOINS)
		{
			for(unsigned int i = 0; i < movement->units.size(); i++)
			{
				if(movement->units[i]->type == Type::attaquant)
				{
					movement->origin->AddUnit(movement->units[i]);
					movement->units.erase(movement->units.begin() + i);
					break;
				}
			}
			return;
		}

		else {return;}

	}

	// touche entrée appuyer : deplacement des unités sélectionnés et fin du tour

	else if(etat == 2 && command->pressedKey == KeyPressed::ENTER)
	{
		
		printf("ici avant seg fault 9\n");
		std::shared_ptr<Movement> movement = std::dynamic_pointer_cast<Movement>(gameState->currentAction);
		movement->unitSelected = false;
		movement->MoveAllUnit();
		gameState->GoToNextAction();
		etat = 0;
	}
}


void GameEngine::ExecuteReinforcementCommand()
{
	std::shared_ptr<Command> command = commands.front();
	static std::shared_ptr<Country> selected_country = std::make_shared<Country>();

	std::shared_ptr<Reinforcements> reinforcement = std::dynamic_pointer_cast<Reinforcements>(gameState->currentAction);
	//static std::shared_ptr<Country> selected_country = std::make_shared<Country>();
	
	if((reinforcement->availableUnits.size() == 0 && reinforcement->selectedUnits.size() == 0) || command->pressedKey == KeyPressed::SPACE_BARRE)
	{
		reinforcement->unitSelected = false;
		gameState->GoToNextAction();
		etat = 0;
		return;
	}

	else if(etat == 0 && command->pressedKey == KeyPressed::LEFT_CLICK)
	{
		
		printf("ici avant seg fault 10\n");
		selected_country = command->countryClicked;
		if(selected_country->owner != gameState->currentPlayer)
		{
			return;
		}
		reinforcement->unitSelected = true;
		etat = 1;
		return;
	}

	else if(etat == 1 && command->pressedKey == KeyPressed::LEFT_CLICK)
	{
		
		printf("ici avant seg fault 11\n");
		if(command->unitClicked == UnitClickedType::DEF_PLUS)
		{
			for(unsigned int i = 0; i < reinforcement->availableUnits.size(); i++)
			{
				if(reinforcement->availableUnits[i]->type == Type::defensif)
				{
					reinforcement->selectedUnits.push_back(reinforcement->availableUnits[i]);
					reinforcement->availableUnits.erase(reinforcement->availableUnits.begin() + i);
					return;
				}
			}
		}

		else if(command->unitClicked == UnitClickedType::DEF_MOINS)
		{
			for(unsigned int i = 0; i < reinforcement->selectedUnits.size(); i++)
			{
				if(reinforcement->selectedUnits[i]->type == Type::defensif)
				{
					reinforcement->availableUnits.push_back(reinforcement->availableUnits[i]);
					reinforcement->selectedUnits.erase(reinforcement->selectedUnits.begin() + i);
					return;
				}
			}
		}

		else if(command->unitClicked == UnitClickedType::NEU_PLUS)
		{
			for(unsigned int i = 0; i < reinforcement->availableUnits.size(); i++)
			{
				if(reinforcement->availableUnits[i]->type == Type::neutre)
				{
					reinforcement->selectedUnits.push_back(reinforcement->availableUnits[i]);
					reinforcement->availableUnits.erase(reinforcement->availableUnits.begin() + i);
					return;
				}
			}
		}

		else if(command->unitClicked == UnitClickedType::NEU_MOINS)
		{
			for(unsigned int i = 0; i < reinforcement->selectedUnits.size(); i++)
			{
				if(reinforcement->selectedUnits[i]->type == Type::neutre)
				{
					reinforcement->availableUnits.push_back(reinforcement->availableUnits[i]);
					reinforcement->selectedUnits.erase(reinforcement->selectedUnits.begin() + i);
					return;
				}
			}
		}

		else if(command->unitClicked == UnitClickedType::ATT_PLUS)
		{
			for(unsigned int i = 0; i < reinforcement->availableUnits.size(); i++)
			{
				if(reinforcement->availableUnits[i]->type == Type::attaquant)
				{
					reinforcement->selectedUnits.push_back(reinforcement->availableUnits[i]);
					reinforcement->availableUnits.erase(reinforcement->availableUnits.begin() + i);
					return;
				}
			}
		}

		else if(command->unitClicked == UnitClickedType::ATT_MOINS)
		{
			for(unsigned int i = 0; i < reinforcement->selectedUnits.size(); i++)
			{
				if(reinforcement->selectedUnits[i]->type == Type::attaquant)
				{
					reinforcement->availableUnits.push_back(reinforcement->availableUnits[i]);
					reinforcement->selectedUnits.erase(reinforcement->selectedUnits.begin() + i);
					return;
				}
			}
		}

		else {return;}
	}

	else if(etat == 1 && command->pressedKey == KeyPressed::ENTER)
	{
		
		printf("ici avant seg fault 12\n");
		while(reinforcement->selectedUnits.size() != 0)
		{
			printf("ici avant seg fault 12.1\n");
			reinforcement->PlaceUnit(reinforcement->selectedUnits[0],selected_country);
		}
		printf("ici avant seg fault 12.2\n");
		reinforcement->unitSelected = false;
		printf("ici avant seg fault 12.3\n");
		etat = 0;
		printf("ici avant seg fault 12.4\n");
		if(reinforcement->availableUnits.size() == 0)
		{
			printf("ici avant seg fault 12.5\n");
			reinforcement->unitSelected = false;
			printf("ici avant seg fault 12.6\n");
			gameState->GoToNextAction();
			printf("ici avant seg fault 12.7\n");
			return;
		}
		printf("ici avant seg fault 12.8\n");
		return;
	}

}


void GameEngine::ExecuteInitialisationCommand()
{
	std::shared_ptr<Country> selected_country = std::make_shared<Country>();
	/*std::shared_ptr<Command> command = commands.front();
	gameState->GoToNextAction();*/


	/*on cherche à déterminé si le pays sélectionné est un pays qui appartien bien à personne si s'est le cas on attribut le pays au joueur. Sinon on passe le tour. Si il n'y a plus de pays libre on fait go to next action*/

	std::shared_ptr<Initialisation> init = std::dynamic_pointer_cast<Initialisation>(gameState->currentAction);
	printf("début ExecuteInitialisationCommand");
	std::shared_ptr<Command> command = commands.front();

	selected_country = command->countryClicked;
	
	for(unsigned int i = 0; i < init->unattributedCountry.size(); i++)
	{
		if (selected_country == init->unattributedCountry[i]){
			init->AttributeCountry(selected_country,gameState->currentPlayer);
		}

	}
	unsigned int j=0;
	//déterminer le current Player
	for(unsigned int i = 0; i < gameState->listPlayer.size(); i++) 
	{
		if (gameState->listPlayer[i]==gameState->currentPlayer){
			unsigned int j=(i+1)%(gameState->listPlayer.size());//on stock la valeur du joueur suivant
			gameState->currentPlayer = gameState->listPlayer[j];
			break;
			//std::shared_ptr<Player> joueur = 
		}
	}

	printf("%i\n",j);

	if(init->unattributedCountry.size() == 0)
		gameState->GoToNextAction();

	//}	
}


void GameEngine::SaveGameState()
{
	std::shared_ptr<GameState> gameState_copy = std::make_shared<GameState>();

	std::thread thread1([&,gameState_copy](){
		for(unsigned int i = 0; i < gameState->listPlayer.size(); i++)
		{
			std::shared_ptr<Player> player_copy = std::make_shared<Player>();
			player_copy->isAnIA = gameState->listPlayer[i]->isAnIA;
			player_copy->id = gameState->listPlayer[i]->id;
			player_copy->color = gameState->listPlayer[i]->color;
			gameState_copy->listPlayer.push_back(player_copy);
			if(gameState->currentPlayer == gameState->listPlayer[i])
			{
				gameState_copy->currentPlayer = player_copy;
			}
			for(unsigned int j = 0; j < gameState->listPlayer[i]->listOwnedCountry.size(); j++)
			{
				for(unsigned int compteur = 0; compteur < gameState->listCountry.size(); compteur++)
				{
					if(gameState->listPlayer[i]->listOwnedCountry[j] == gameState->listCountry[compteur])
					{
						gameState_copy->listPlayer[i]->AddOwnedCountry(gameState_copy->listCountry[compteur]);
						gameState_copy->listCountry[compteur]->owner = gameState_copy->listPlayer[i];
						break;
					}
				}
			}
		}
	});

	std::thread thread2([&,gameState_copy](){
		for(unsigned int i = 0; i < gameState->listCountry.size(); i++)
		{
			for(unsigned int j = 0; j < gameState->listCountry[i]->listUnit.size(); j++)
			{
				std::shared_ptr<Unit> unit_copy = std::make_shared<Unit>();
				if(gameState->listCountry[i]->listUnit[j]->type == Type::attaquant)
				{
					unit_copy->type = Type::attaquant;
					gameState_copy->listCountry[i]->AddUnit(unit_copy);
				}
				else if(gameState->listCountry[i]->listUnit[j]->type == Type::defensif)
				{
					unit_copy->type = Type::defensif;
					gameState_copy->listCountry[i]->AddUnit(unit_copy);
				}
				else
				{
					unit_copy->type = Type::neutre;
					gameState_copy->listCountry[i]->AddUnit(unit_copy);
				}
			}
		}

	});

	std::thread thread3([&,gameState_copy](){
		if(gameState->currentAction->GetActionType() == ActionType::_ATTACK)
		{
			std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(gameState->currentAction);
			std::shared_ptr<Attack> attack_copy = std::make_shared<Attack>();

			std::thread thread3_1([&,gameState_copy, attack, attack_copy](){
				for(unsigned int i = 0; i < gameState->listCountry.size(); i++)
				{
					if(attack->attackerCountry == gameState->listCountry[i])
					{
						attack_copy->attackerCountry = gameState_copy->listCountry[i];
					}
					else if(attack->defencerCountry == gameState->listCountry[i])
					{
						attack_copy->defencerCountry = gameState_copy->listCountry[i];
					}
				}
			});

			std::thread thread3_2([&,gameState_copy, attack, attack_copy](){
				for(unsigned int i = 0; i < attack->attackerUnits.size(); i++)
				{
					std::shared_ptr<Unit> unit_copy = std::make_shared<Unit>();
					if(attack->attackerUnits[i]->type == Type::attaquant)
					{
						unit_copy->type = Type::attaquant;
						attack_copy->attackerUnits.push_back(unit_copy);
					}
					if(attack->attackerUnits[i]->type == Type::defensif)
					{
						unit_copy->type = Type::defensif;
						attack_copy->attackerUnits.push_back(unit_copy);
					}
					if(attack->attackerUnits[i]->type == Type::neutre)
					{
						unit_copy->type = Type::neutre;
						attack_copy->attackerUnits.push_back(unit_copy);
					}
				}
			});

			std::thread thread3_3([&,gameState_copy, attack, attack_copy](){
				for(unsigned int i = 0; i < attack->defencerUnits.size(); i++)
				{
					std::shared_ptr<Unit> unit_copy = std::make_shared<Unit>();
					if(attack->defencerUnits[i]->type == Type::attaquant)
					{
						unit_copy->type = Type::attaquant;
						attack_copy->defencerUnits.push_back(unit_copy);
					}
					if(attack->defencerUnits[i]->type == Type::defensif)
					{
						unit_copy->type = Type::defensif;
						attack_copy->defencerUnits.push_back(unit_copy);
					}
					if(attack->defencerUnits[i]->type == Type::neutre)
					{
						unit_copy->type = Type::neutre;
						attack_copy->defencerUnits.push_back(unit_copy);
					}
				}
			});

			thread3_1.join();
			thread3_2.join();
			thread3_3.join();

			attack_copy->unitSelected = attack->unitSelected;
			attack_copy->displayAttack = attack->displayAttack;

			gameState_copy->currentAction = attack_copy;
		}

		if(gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
		{
			std::shared_ptr<Movement> movement = std::dynamic_pointer_cast<Movement>(gameState->currentAction);
			std::shared_ptr<Movement> movement_copy = std::make_shared<Movement>();

			std::thread thread3_1([&,gameState_copy, movement, movement_copy](){
				for(unsigned int i = 0; i < gameState->listCountry.size(); i++)
				{
					if(movement->origin == gameState->listCountry[i])
					{
						movement_copy->origin = gameState_copy->listCountry[i];
					}
					else if(movement->destination == gameState->listCountry[i])
					{
						movement_copy->destination = gameState_copy->listCountry[i];
					}
				}
			});

			std::thread thread3_2([&,gameState_copy, movement, movement_copy](){
				for(unsigned int i = 0; i < movement->units.size(); i++)
				{
					std::shared_ptr<Unit> unit_copy = std::make_shared<Unit>();
					if(movement->units[i]->type == Type::attaquant)
					{
						unit_copy->type = Type::attaquant;
						movement_copy->units.push_back(unit_copy);
					}
					if(movement->units[i]->type == Type::defensif)
					{
						unit_copy->type = Type::defensif;
						movement_copy->units.push_back(unit_copy);
					}
					if(movement->units[i]->type == Type::neutre)
					{
						unit_copy->type = Type::neutre;
						movement_copy->units.push_back(unit_copy);
					}
				}
			});

			thread3_1.join();
			thread3_2.join();

			movement_copy->unitSelected = movement->unitSelected;
			gameState_copy->currentAction = movement_copy;
		}

		if(gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
		{
			std::shared_ptr<Reinforcements> reinforcement = std::dynamic_pointer_cast<Reinforcements>(gameState->currentAction);
			std::shared_ptr<Reinforcements> reinforcement_copy = std::make_shared<Reinforcements>();

			std::thread thread3_1([&,gameState_copy, reinforcement, reinforcement_copy](){
				for(unsigned int i = 0; i < gameState->listCountry.size(); i++)
				{
					for(unsigned int j = 0; j < reinforcement->availableCountry.size(); j++)
					{
						if(gameState->listCountry[i] == reinforcement->availableCountry[j])
						{
							reinforcement_copy->availableCountry.push_back(gameState_copy->listCountry[i]);
							break;
						}
					}
				}
			});

			std::thread thread3_2([&,gameState_copy, reinforcement, reinforcement_copy](){
				for(unsigned int i = 0; i < reinforcement->availableUnits.size(); i++)
				{
					std::shared_ptr<Unit> unit_copy = std::make_shared<Unit>();
					if(reinforcement->availableUnits[i]->type == Type::attaquant)
					{
						unit_copy->type = Type::attaquant;
						reinforcement_copy->availableUnits.push_back(unit_copy);
					}
					if(reinforcement->availableUnits[i]->type == Type::defensif)
					{
						unit_copy->type = Type::defensif;
						reinforcement_copy->availableUnits.push_back(unit_copy);
					}
					if(reinforcement->availableUnits[i]->type == Type::neutre)
					{
						unit_copy->type = Type::neutre;
						reinforcement_copy->availableUnits.push_back(unit_copy);
					}
				}
			});

			std::thread thread3_3([&,gameState_copy, reinforcement, reinforcement_copy](){
				for(unsigned int i = 0; i < reinforcement->selectedUnits.size(); i++)
				{
					std::shared_ptr<Unit> unit_copy = std::make_shared<Unit>();
					if(reinforcement->selectedUnits[i]->type == Type::attaquant)
					{
						unit_copy->type = Type::attaquant;
						reinforcement_copy->selectedUnits.push_back(unit_copy);
					}
					if(reinforcement->selectedUnits[i]->type == Type::defensif)
					{
						unit_copy->type = Type::defensif;
						reinforcement_copy->selectedUnits.push_back(unit_copy);
					}
					if(reinforcement->selectedUnits[i]->type == Type::neutre)
					{
						unit_copy->type = Type::neutre;
						reinforcement_copy->selectedUnits.push_back(unit_copy);
					}
				}
			});

			thread3_1.join();
			thread3_2.join();
			thread3_3.join();

			reinforcement_copy->unitSelected = reinforcement->unitSelected;
			gameState_copy->currentAction = reinforcement_copy;
		}

	});

	thread1.join();
	thread2.join();
	thread3.join();

	//return(gameState_copy);
	rollback.push(gameState_copy);
}







