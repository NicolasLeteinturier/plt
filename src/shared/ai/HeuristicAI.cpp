#include <queue>
#include "HeuristicAI.h"
#include <stdlib.h>
#include "../../define.h"
#include "../state/Attack.h"
#include "../state/Movement.h"
#include "../state/Initialisation.h"
//#include "../state/Player.h"////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace ai;
using namespace state;
using namespace engine;

HeuristicAI::HeuristicAI()
{
}


void HeuristicAI::play()
{
	if(engine->gameState->currentPlayer->isAnIA != IAType::HEURISTIC)
	{
		return;
	}

	printf("Heuristic IA playing\n");

	if(engine->gameState->currentAction->GetActionType() == ActionType::_INITIALISATION)
	{
		//initialisation 
		std::shared_ptr<Initialisation> init = std::dynamic_pointer_cast<Initialisation>(engine->gameState->currentAction);
		//std::shared_ptr<Player> Player = std::dynamic_pointer_cast<Player>(engine->gameState->Player);
		bool turnDone = false;

		if(init->unattributedCountry.size()>0)
			{
			for(unsigned int i = 0; i < engine->gameState->currentPlayer->listOwnedCountry.size(); i++)				
				{
				for(unsigned int j = 0; j < engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor.size(); j++)			
					{
					for(unsigned int k = 0; k < init->unattributedCountry.size(); k++)
						{
						if (engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]==init->unattributedCountry[k])
							{
							if(turnDone == false)
								{
								turnDone = true;
				 				init->AttributeCountry(init->unattributedCountry[k],engine->gameState->currentPlayer);
								}
							}
						}
					}
				}
				
			init->AttributeCountry(init->unattributedCountry[0],engine->gameState->currentPlayer);
			}
		// géstion des joueur
		for(unsigned int i = 0; i < engine->gameState->listPlayer.size(); i++) 
		{
			if (engine->gameState->listPlayer[i]==engine->gameState->currentPlayer){
				unsigned int j=(i+1)%(engine->gameState->listPlayer.size());//on stock la valeur du joueur suivant
				engine->gameState->currentPlayer = engine->gameState->listPlayer[j];
				break;
				//std::shared_ptr<Player> joueur = 
			}
		}
	}

	else if(engine->gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
	{
		engine->gameState->GoToNextAction();
	}

	else if(engine->gameState->currentAction->GetActionType() == ActionType::_ATTACK)
	{
		//printf("\nIA debut phase attaque\n");
		std::shared_ptr<Country> originCountry = std::make_shared<Country>();
		std::shared_ptr<Country> destinationCountry = std::make_shared<Country>();

		//chercher le pays ayant le moins de voisin enemie
		int max,min;
		max = 0;
		
		/*for(unsigned int i = 0; i < engine->gameState->currentPlayer->listOwnedCountry.size(); i++)
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
		}*/

		int max_difference = -30;
		for(unsigned int i = 0; i < engine->gameState->currentPlayer->listOwnedCountry.size(); i++)
		{
			for(unsigned int j = 0; j < engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor.size(); j++)
			{
				if(engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]->owner != engine->gameState->currentPlayer)
				{				
					int diff = (engine->gameState->currentPlayer->listOwnedCountry[i]->FindTypeNumber(Type::attaquant) - engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]->FindTypeNumber(Type::defensif))/*/((engine->gameState->currentPlayer->listOwnedCountry[i]->listUnit.size() + engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]->listUnit.size())/2)*/;
					if(diff > max_difference)
					{
						originCountry = engine->gameState->currentPlayer->listOwnedCountry[i];
						destinationCountry = engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j];
						max_difference = diff;
					}
				}
			}
		}

		if(max_difference == -30)
		{
			std::shared_ptr<Command> commandspace = std::make_shared<Command>();
			commandspace->pressedKey = KeyPressed::ESCAPE;
			engine->commands.push(commandspace);
			return;
		}

		unsigned int nbUnitAtt = originCountry->FindTypeNumber(Type::attaquant);
		unsigned int nbUnitNeu = originCountry->FindTypeNumber(Type::neutre)/3;

		std::shared_ptr<Command> commandor = std::make_shared<Command>();
		std::shared_ptr<Command> commanddest = std::make_shared<Command>();
		std::shared_ptr<Command> commandfin = std::make_shared<Command>();

		commandor->countryClicked = originCountry;
		commandor->unitClicked = UnitClickedType::NONE;
		commandor->pressedKey = KeyPressed::LEFT_CLICK;

		commanddest->countryClicked = destinationCountry;
		commanddest->unitClicked = UnitClickedType::NONE;
		commanddest->pressedKey = KeyPressed::LEFT_CLICK;

		engine->commands.push(commandor);
		engine->commands.push(commanddest);

		for(unsigned int i = 0; i < nbUnitAtt; i++)
		{
			std::shared_ptr<Command> commandunitatt = std::make_shared<Command>();
			commandunitatt->unitClicked = UnitClickedType::ATT_PLUS;
			commandunitatt->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitatt);
		}

		for(unsigned int i = 0; i < nbUnitNeu; i++)
		{
			std::shared_ptr<Command> commandunitdef = std::make_shared<Command>();
			commandunitdef->unitClicked = UnitClickedType::NEU_PLUS;
			commandunitdef->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitdef);
		}

	commandfin->pressedKey = KeyPressed::ENTER;
	engine->commands.push(commandfin);

	std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(engine->gameState->currentAction);

	for(unsigned int i = 0; i < attack->defencerUnits.size() + attack->attackerUnits.size(); i++)
	{
		std::shared_ptr<Command> commandspace = std::make_shared<Command>();
		commandspace->pressedKey = KeyPressed::SPACE_BARRE;
		engine->commands.push(commandspace);
	}

	//printf("\nIA fin phase attaque\n");
	}




//Movement-----------------------------------



	else if(engine->gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
	{
		//printf("\nIA debut phase Mouvement\n");
		std::shared_ptr<Country> originCountry = std::make_shared<Country>();
		std::shared_ptr<Country> destinationCountry = std::make_shared<Country>();

		//chercher le pays ayant le moins de voisin enemie

		unsigned int min = 18;
		unsigned int max_unit = 0;

		for(unsigned int i = 0; i < engine->gameState->currentPlayer->listOwnedCountry.size(); i++)
		{
			unsigned int compteur = 0;
			for(unsigned int j = 0; j < engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor.size(); j++)
			{
				if(engine->gameState->currentPlayer->listOwnedCountry[i]->neighboor[j]->owner != engine->gameState->currentPlayer)
				{
					compteur++;//determine le nombre de voisin enemi
				}	
			}
			if(compteur < min || (compteur == min && engine->gameState->currentPlayer->listOwnedCountry[i]->listUnit.size() > max_unit))
			{
				min = compteur;
				max_unit = engine->gameState->currentPlayer->listOwnedCountry[i]->listUnit.size();
				originCountry = engine->gameState->currentPlayer->listOwnedCountry[i];//choix du pays d'origine avec le moiins de voisins 
			}
		}

		unsigned int max = 0;
		unsigned int min_unit = 1000;

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
			if(max < compteur || (compteur == max && engine->gameState->currentPlayer->listOwnedCountry[i]->listUnit.size() < min_unit))
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
				commandor->countryClicked = originCountry;
				commandor->pressedKey = KeyPressed::LEFT_CLICK;
			}
			else if (engine->gameState->listCountry[i] == destinationCountry){
				commanddest->countryClicked = destinationCountry;
				commanddest->pressedKey = KeyPressed::LEFT_CLICK;
			}
		}

		engine->commands.push(commandor);
		engine->commands.push(commanddest);
		if(nbUnitAtt!=0){
		for(unsigned int i = 0; i < nbUnitAtt; i++)
		{
			std::shared_ptr<Command> commandunitatt = std::make_shared<Command>();
			commandunitatt->unitClicked = UnitClickedType::ATT_PLUS;
			commandunitatt->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitatt);
		}
}
		if(nbUnitDef!=0){
		for(unsigned int i = 0; i < nbUnitDef; i++)
		{
			std::shared_ptr<Command> commandunitdef = std::make_shared<Command>();
			commandunitdef->unitClicked = UnitClickedType::DEF_PLUS;
			commandunitdef->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitdef);
		}
}
		if(nbUnitNeu!=0){
		for(unsigned int i = 0; i < nbUnitNeu; i++)
		{
			std::shared_ptr<Command> commandunitneu = std::make_shared<Command>();
			commandunitneu->unitClicked = UnitClickedType::NEU_PLUS;
			commandunitneu->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandunitneu);
		}
}
		//printf("\nIA fin phase Mouvement\n");
		commandfin->pressedKey = KeyPressed::ENTER;
		engine->commands.push(commandfin);

		return;
		
	}
}

