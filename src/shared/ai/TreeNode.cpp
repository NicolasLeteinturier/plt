#include <queue>
#include "TreeNode.h"
#include <thread>
#include "../state.h"
#include <iostream>


using namespace ai;
using namespace engine;
using namespace state;

TreeNode::TreeNode()
{
}


void TreeNode::BuildLeaf()
{
	if(leafs.size() != 0)
	{
		printf("les feuilles sont déjà construite\n");
		return;
	}

	// generation des differentes possibilités d'attaques
	else if(gameState->currentAction->GetActionType() == ActionType::_ATTACK)
	{
		for(unsigned int i = 0; i < gameState->currentPlayer->listOwnedCountry.size(); i++)
		{
			for(unsigned int j = 0; j < gameState->currentPlayer->listOwnedCountry[i]->neighboor.size(); j++)
			{
				if(gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]->owner != gameState->currentPlayer)
				{
					std::shared_ptr<TreeNode> treenode = std::make_shared<TreeNode>();
					treenode->gameState = CopyGameState();
					std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
					gameEngine->gameState = treenode->gameState;
					leafs.push_back(treenode);

					std::shared_ptr<Command> commandor = std::make_shared<Command>();
					std::shared_ptr<Command> commanddest = std::make_shared<Command>();
					std::shared_ptr<Command> commandfin = std::make_shared<Command>();

					commandor->countryClicked = treenode->gameState->currentPlayer->listOwnedCountry[i];
					commandor->unitClicked = UnitClickedType::NONE;
					commandor->pressedKey = KeyPressed::LEFT_CLICK;

					commanddest->countryClicked = treenode->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j];
					commanddest->unitClicked = UnitClickedType::NONE;
					commanddest->pressedKey = KeyPressed::LEFT_CLICK;

					unsigned int nbUnitAtt = treenode->gameState->currentPlayer->listOwnedCountry[i]->FindTypeNumber(Type::attaquant);
					unsigned int nbUnitNeu = treenode->gameState->currentPlayer->listOwnedCountry[i]->FindTypeNumber(Type::neutre)/3;

					gameEngine->commands.push(commandor);
					gameEngine->commands.push(commanddest);

					for(unsigned int k = 0; k < nbUnitAtt; k++)
					{
						std::shared_ptr<Command> commandunitatt = std::make_shared<Command>();
						commandunitatt->unitClicked = UnitClickedType::ATT_PLUS;
						commandunitatt->pressedKey = KeyPressed::LEFT_CLICK;
						gameEngine->commands.push(commandunitatt);
					}

					for(unsigned int k = 0; k < nbUnitNeu; k++)
					{
						std::shared_ptr<Command> commandunitdef = std::make_shared<Command>();
						commandunitdef->unitClicked = UnitClickedType::NEU_PLUS;
						commandunitdef->pressedKey = KeyPressed::LEFT_CLICK;
						gameEngine->commands.push(commandunitdef);
					}

					commandfin->pressedKey = KeyPressed::ENTER;
					gameEngine->commands.push(commandfin);

					for(unsigned int k = 0; k < (nbUnitAtt + nbUnitNeu + treenode->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]->listUnit.size() + 1); k++)
					{
						std::shared_ptr<Command> commandspace = std::make_shared<Command>();
						commandspace->pressedKey = KeyPressed::SPACE_BARRE;
						gameEngine->commands.push(commandspace);
					}

					gameEngine->ExecuteCommands();
				}
			}
		}

		std::shared_ptr<TreeNode> treenode = std::make_shared<TreeNode>();
		treenode->gameState = CopyGameState();
		std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
		gameEngine->gameState = treenode->gameState;
		leafs.push_back(treenode);

		std::shared_ptr<Command> commandor = std::make_shared<Command>();
		commandor->pressedKey = KeyPressed::ESCAPE;
		gameEngine->commands.push(commandor);

		return;
	}

	// generation des differentes possibilités de mouvement
	else if(gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
	{
		for(unsigned int i = 0; i < gameState->currentPlayer->listOwnedCountry.size(); i++)
		{
			for(unsigned int j = 0; j < gameState->currentPlayer->listOwnedCountry.size(); j++)
			{
				if(i != j)
				{
					std::shared_ptr<TreeNode> treenode = std::make_shared<TreeNode>();
					treenode->gameState = CopyGameState();
					std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
					gameEngine->gameState = treenode->gameState;
					leafs.push_back(treenode);

					std::shared_ptr<Command> commandor = std::make_shared<Command>();
					std::shared_ptr<Command> commanddest = std::make_shared<Command>();
					std::shared_ptr<Command> commandfin = std::make_shared<Command>();

					commandor->countryClicked = treenode->gameState->currentPlayer->listOwnedCountry[i];
					commandor->unitClicked = UnitClickedType::NONE;
					commandor->pressedKey = KeyPressed::LEFT_CLICK;

					commanddest->countryClicked = treenode->gameState->currentPlayer->listOwnedCountry[j];
					commanddest->unitClicked = UnitClickedType::NONE;
					commanddest->pressedKey = KeyPressed::LEFT_CLICK;

					gameEngine->commands.push(commandor);
					gameEngine->commands.push(commanddest);

					unsigned int nbUnitAtt = treenode->gameState->currentPlayer->listOwnedCountry[i]->FindTypeNumber(Type::attaquant)/2;
					unsigned int nbUnitDef = treenode->gameState->currentPlayer->listOwnedCountry[i]->FindTypeNumber(Type::defensif)/2;
					unsigned int nbUnitNeu = treenode->gameState->currentPlayer->listOwnedCountry[i]->FindTypeNumber(Type::neutre)/2;

					for(unsigned int i = 0; i < nbUnitAtt; i++)
					{
						std::shared_ptr<Command> commandunitatt = std::make_shared<Command>();
						commandunitatt->unitClicked = UnitClickedType::ATT_PLUS;
						commandunitatt->pressedKey = KeyPressed::LEFT_CLICK;
						gameEngine->commands.push(commandunitatt);
					}

					for(unsigned int i = 0; i < nbUnitDef; i++)
					{
						std::shared_ptr<Command> commandunitdef = std::make_shared<Command>();
						commandunitdef->unitClicked = UnitClickedType::DEF_PLUS;
						commandunitdef->pressedKey = KeyPressed::LEFT_CLICK;
						gameEngine->commands.push(commandunitdef);
					}

					for(unsigned int i = 0; i < nbUnitNeu; i++)
					{
						std::shared_ptr<Command> commandunitneu = std::make_shared<Command>();
						commandunitneu->unitClicked = UnitClickedType::NEU_PLUS;
						commandunitneu->pressedKey = KeyPressed::LEFT_CLICK;
						gameEngine->commands.push(commandunitneu);
					}

					commandfin->pressedKey = KeyPressed::ENTER;
					gameEngine->commands.push(commandfin);

					gameEngine->ExecuteCommands();
				}
			}
		}

		return;
	}

	else if(gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
	{
		for(unsigned int i = 0; i < gameState->currentPlayer->listOwnedCountry.size(); i++)
		{
			std::shared_ptr<TreeNode> treenode = std::make_shared<TreeNode>();
			treenode->gameState = CopyGameState();
			std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
			gameEngine->gameState = treenode->gameState;
			leafs.push_back(treenode);

			std::shared_ptr<Command> commanddest = std::make_shared<Command>();
			std::shared_ptr<Command> commandfin = std::make_shared<Command>();

			commanddest->countryClicked = treenode->gameState->currentPlayer->listOwnedCountry[i];
			commanddest->unitClicked = UnitClickedType::NONE;
			commanddest->pressedKey = KeyPressed::LEFT_CLICK;
	
			printf("ici avant seg fault reinforcement\n");

			for(unsigned int j = 0; j < gameState->currentPlayer->ReinforcementNumber(); j++)
			{
				std::shared_ptr<Command> commandunitatt = std::make_shared<Command>();
				commandunitatt->unitClicked = UnitClickedType::ATT_PLUS;
				commandunitatt->pressedKey = KeyPressed::LEFT_CLICK;
				gameEngine->commands.push(commandunitatt);
			}

			for(unsigned int j = 0; j < gameState->currentPlayer->ReinforcementNumber(); j++)
			{
				std::shared_ptr<Command> commandunitdef = std::make_shared<Command>();
				commandunitdef->unitClicked = UnitClickedType::DEF_PLUS;
				commandunitdef->pressedKey = KeyPressed::LEFT_CLICK;
				gameEngine->commands.push(commandunitdef);
			}

			for(unsigned int j = 0; j < gameState->currentPlayer->ReinforcementNumber(); j++)
			{
				std::shared_ptr<Command> commandunitneu = std::make_shared<Command>();
				commandunitneu->unitClicked = UnitClickedType::NEU_PLUS;
				commandunitneu->pressedKey = KeyPressed::LEFT_CLICK;
				gameEngine->commands.push(commandunitneu);
			}

			commandfin->pressedKey = KeyPressed::ENTER;
			gameEngine->commands.push(commandfin);

			gameEngine->ExecuteCommands();
		}

		return;
	}

	else{printf("je sais pas dans quel etat tu es ...\n");}

	return;
}


std::shared_ptr<GameState> TreeNode::CopyGameState()
{
	std::shared_ptr<GameState> gameState_copy = std::make_shared<GameState>();

	std::thread thread1([&,gameState_copy](){
		for(unsigned int i = 0; i < gameState->listPlayer.size(); i++)
		{
			std::shared_ptr<Player> player_copy = std::make_shared<Player>();
			player_copy->isAnIA = gameState->listPlayer[i]->isAnIA;
			player_copy->id = gameState->listPlayer[i]->id;
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

	return(gameState_copy);
}
