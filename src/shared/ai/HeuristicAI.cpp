#include <queue>
#include "HeuristicAI.h"
#include <stdlib.h>
#include "../../define.h"
#include "../state/Attack.h"
#include "../state/Movement.h"

using namespace ai;
using namespace state;
using namespace engine;

HeuristicAI::HeuristicAI()
{
}


void HeuristicAI::play()
{
	/*variables Globales*/
	unsigned int tabX[NB_COUNTRY]={UNIT_POS_X};
	unsigned int tabY[NB_COUNTRY]={UNIT_POS_Y};		
	
	if(engine->gameState->currentPlayer->isAnIA == IAType::HEURISTIC)
	{
		return;
	}

	if(engine->gameState->currentAction->GetActionType() == ActionType::_INITIALISATION)
	{
		return;
	}

	else if(engine->gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
	{
		engine->gameState->GoToNextAction();
	}

	else if(engine->gameState->currentAction->GetActionType() == ActionType::_ATTACK)
	{
		printf("\nIA debut phase attaque\n");
		std::shared_ptr<Country> originCountry = std::make_shared<Country>();
		std::shared_ptr<Country> destinationCountry = std::make_shared<Country>();

		//chercher le pays ayant le moins de voisin enemie
		int max,min;
		max = 0;
		
		for(unsigned int i = 0; i < engine->gameState->currentPlayer->listOwnedCountry.size(); i++)
		{
			unsigned int nbUnitAtt = engine->gameState->currentPlayer->listOwnedCountry[i]->FindTypeNumber(Type::attaquant);
			if(nbUnitAtt>max){
				max = nbUnitAtt;
				originCountry = engine->gameState->currentPlayer->listOwnedCountry[i];}//choix du pays d'origine avec le plus d'unité offencives
		}

		//chercher le pays avec le moins d'enemie
		int compteur = 0;
		min=9999999;

			for(unsigned int j = 0; j < originCountry->neighboor.size(); j++)
			{
				if(originCountry->neighboor[j]->owner != engine->gameState->currentPlayer)//on cherche dans les pays ennemies
				{
					compteur++;
					if (min>originCountry->neighboor[j]->FindTypeNumber(Type::defensif)){
						min=originCountry->neighboor[j]->FindTypeNumber(Type::defensif);
						destinationCountry=originCountry->neighboor[j];
				}	
			}
			if(compteur==0)
			{
				std::shared_ptr<Command> commandspace = std::make_shared<Command>();
				commandspace->pressedKey = KeyPressed::ESCAPE;
				engine->commands.push(commandspace);
				return;
			}
		}

		unsigned int nbUnitAtt = originCountry->FindTypeNumber(Type::attaquant);
		unsigned int nbUnitNeu = originCountry->FindTypeNumber(Type::neutre)/3;

		std::shared_ptr<Command> commandor = std::make_shared<Command>();
		std::shared_ptr<Command> commanddest = std::make_shared<Command>();
		std::shared_ptr<Command> commandfin = std::make_shared<Command>();

		for(unsigned int i = 0; i < engine->gameState->listCountry.size(); i++){
			if (engine->gameState->listCountry[i] == originCountry){
				commandor->mousePositionX = tabX[i];	
				commandor->mousePositionY = tabY[i];
				commandor->pressedKey = KeyPressed::LEFT_CLICK;
			}
			else if (engine->gameState->listCountry[i] == destinationCountry){
				commanddest->mousePositionX = tabX[i];	
				commanddest->mousePositionY = tabY[i];
				commanddest->pressedKey = KeyPressed::LEFT_CLICK;
			}
		}

		engine->commands.push(commandor);
		engine->commands.push(commanddest);

		for(unsigned int i = 0; i < nbUnitAtt; i++)
		{
			std::shared_ptr<Command> commandunitatt = std::make_shared<Command>();
			commandunitatt->mousePositionX = 800;	
			commandunitatt->mousePositionY = 130;
			commandunitatt->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitatt);
		}

		for(unsigned int i = 0; i < nbUnitNeu; i++)
		{
			std::shared_ptr<Command> commandunitdef = std::make_shared<Command>();
			commandunitdef->mousePositionX = 300;	
			commandunitdef->mousePositionY = 130;
			commandunitdef->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitdef);
		}

	commandfin->pressedKey = KeyPressed::ENTER;
	engine->commands.push(commandfin);

	std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(engine->gameState->currentAction);

	/*while(attack->defencerUnits.size() != 0 && attack->attackerUnits.size() != 0)
	{*/
		std::shared_ptr<Command> commandspace = std::make_shared<Command>();
		commandspace->pressedKey = KeyPressed::SPACE_BARRE;
		engine->commands.push(commandspace);
	/*}*/

	printf("\nIA fin phase attaque\n");
	}




//Movement-----------------------------------



	else if(engine->gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
	{
		printf("\nIA debut phase Mouvement\n");
		std::shared_ptr<Country> originCountry = std::make_shared<Country>();
		std::shared_ptr<Country> destinationCountry = std::make_shared<Country>();

		//chercher le pays ayant le moins de voisin enemie

		unsigned int min = 18;

		for(unsigned int i = 0; i < engine->gameState->currentPlayer->listOwnedCountry.size(); i++)
		{
			unsigned int compteur = 0;
			for(unsigned int j = 0; j < engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor.size(); j++)
			{
				if(engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]->owner != engine->gameState->currentPlayer)
				{
					compteur++;//determine le nombre de voisin énemie 
				}	
			}
			if(compteur < min)
			{
				min = compteur;
				originCountry = engine->gameState->currentPlayer->listOwnedCountry[i];//choix du pays d'origine avec le moiins de voisins 
			}
		}

		unsigned int max = 0;

		//chercher le pays avec le plus d'enemie
		for(unsigned int i = 0; i < engine->gameState->currentPlayer->listOwnedCountry.size(); i++)
		{
			unsigned int compteur = 0;
			for(unsigned int j = 0; j < engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor.size(); j++)
			{
				if(engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]->owner != engine->gameState->currentPlayer)
				{
					compteur++;
				}	
			}
			if(max < compteur)
			{
				max = compteur;
				destinationCountry = engine->gameState->currentPlayer->listOwnedCountry[i];//choix du pays de déstination avec le plus de voisins 
			}
		}

		unsigned int nbUnitAtt = originCountry->FindTypeNumber(Type::attaquant)/2;
		unsigned int nbUnitDef = originCountry->FindTypeNumber(Type::defensif)/2;
		unsigned int nbUnitNeu = originCountry->FindTypeNumber(Type::neutre)/2;

		std::shared_ptr<Command> commandor = std::make_shared<Command>();
		std::shared_ptr<Command> commanddest = std::make_shared<Command>();
		std::shared_ptr<Command> commandfin = std::make_shared<Command>();

		for(unsigned int i = 0; i < engine->gameState->listCountry.size(); i++){
			if (engine->gameState->listCountry[i] == originCountry){
				commandor->mousePositionX = tabX[i];	
				commandor->mousePositionY = tabY[i];
				printf("%d\n",tabX[i]);
				printf("%d\n",tabY[i]);
				commandor->pressedKey = KeyPressed::LEFT_CLICK;
			}
			else if (engine->gameState->listCountry[i] == destinationCountry){
				commanddest->mousePositionX = tabX[i];	
				commanddest->mousePositionY = tabY[i];
				printf("%d\n",tabX[i]);
				printf("%d\n",tabY[i]);
				commanddest->pressedKey = KeyPressed::LEFT_CLICK;
			}
		}

		engine->commands.push(commandor);
		engine->commands.push(commanddest);
		if(nbUnitAtt!=0){
		for(unsigned int i = 0; i < nbUnitAtt; i++)
		{
			std::shared_ptr<Command> commandunitatt = std::make_shared<Command>();
			commandunitatt->mousePositionX = 800;	
			commandunitatt->mousePositionY = 130;
			commandunitatt->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitatt);
		}
}
		if(nbUnitDef!=0){
		for(unsigned int i = 0; i < nbUnitDef; i++)
		{
			std::shared_ptr<Command> commandunitdef = std::make_shared<Command>();
			commandunitdef->mousePositionX = 300;	
			commandunitdef->mousePositionY = 130;
			commandunitdef->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitdef);
		}
}
		if(nbUnitNeu!=0){
		for(unsigned int i = 0; i < nbUnitNeu; i++)
		{
			std::shared_ptr<Command> commandunitneu = std::make_shared<Command>();
			commandunitneu->mousePositionX = 600;	
			commandunitneu->mousePositionY = 130;
			commandunitneu->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitneu);
		}
}
		printf("\nIA fin phase Mouvement\n");
		commandfin->pressedKey = KeyPressed::ENTER;
		engine->commands.push(commandfin);

		return;
		
	}
}

