#include <queue>
#include "TreeNode.h"
#include <thread>
#include "../state.h"


using namespace ai;
using namespace engine;
using namespace state;

TreeNode::TreeNode()
{
}

std::shared_ptr<GameState> TreeNode::CopyGameState()
{
	std::shared_ptr<GameState> gameState_copy = std::make_shared<GameState>();

	std::thread thread1([&,gameState_copy](){
		for(unsigned int i = 0; i < gameState->listPlayer.size(); i++)
		{
			gameState_copy->AddPlayer(gameState->listPlayer[i]->isAnIA, gameState->listPlayer[i]->id);
			if(gameState->currentPlayer == gameState->listPlayer[i])
			{
				gameState_copy->currentPlayer = gameState_copy->listPlayer[i];
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

	printf("arriver jusqu'ici\n");

	thread1.join();
	thread2.join();
	thread3.join();

	return(gameState_copy);
}
