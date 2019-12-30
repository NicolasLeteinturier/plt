#include <queue>
#include "RandomAI.h"
#include <stdlib.h>
#include "../../define.h"
#include "../state/Attack.h"
#include "../state/Initialisation.h"

using namespace ai;
using namespace state;
using namespace engine;

RandomAI::RandomAI()
{
}


void RandomAI::play()
{	
	
	if(engine->gameState->currentPlayer->isAnIA != IAType::RANDOM)
	{
		return;
	}

	printf("Random IA playing\n");

	if(engine->gameState->currentAction->GetActionType() == ActionType::_INITIALISATION)
	{

	//initialisation 
		std::shared_ptr<Initialisation> init = std::dynamic_pointer_cast<Initialisation>(engine->gameState->currentAction);


		if(init->unattributedCountry.size()>0)
			init->AttributeCountry(init->unattributedCountry[0],engine->gameState->currentPlayer);
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
		//creation des objets
		std::shared_ptr<Player> player = engine->gameState->currentPlayer;
		std::shared_ptr<Command> commandor = std::make_shared<Command>();
		std::shared_ptr<Command> commanddest = std::make_shared<Command>();
		std::shared_ptr<Command> commandu1 = std::make_shared<Command>();
		std::shared_ptr<Command> commandu2 = std::make_shared<Command>();
		std::shared_ptr<Command> commandu3 = std::make_shared<Command>();
		std::shared_ptr<Command> commandu4 = std::make_shared<Command>();
		std::shared_ptr<Command> commandfin = std::make_shared<Command>();
		//choix du pays attaquant
		unsigned int n = player->listOwnedCountry.size();
		int originCountry = rand() % n;
		//générer les clicks de l'IA
	
//choix pays attaquant

		commandor->countryClicked = player->listOwnedCountry[originCountry];
		commandor->unitClicked = UnitClickedType::NONE;
		commandor->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandor);

		//choix du pays à attaquer

		n = player->listOwnedCountry[originCountry]->neighboor.size();
		int destCountry = rand() % n;


//choix du pays à attaquer
		if(player->listOwnedCountry[originCountry]->neighboor[destCountry]->owner != player)
		{
			commanddest->countryClicked = player->listOwnedCountry[originCountry]->neighboor[destCountry];	
			commanddest->unitClicked = UnitClickedType::NONE;
			commanddest->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commanddest);
		}
		else
		{
			commandfin->pressedKey = KeyPressed::ESCAPE;
			commandfin->unitClicked = UnitClickedType::NONE;
			engine->commands.push(commandfin);
			return;
		}

		//choix des unités à deplacer	
		int selector1 = rand() % 3;
		int selector2 = rand() % 3;
		int selector3 = rand() % 3;
		int selector4 = rand() % 3;

		if (selector1 == 0){
			commandu1->unitClicked = UnitClickedType::DEF_PLUS;
			commandu1->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu1);}
		if (selector1 == 1){
			commandu1->unitClicked = UnitClickedType::NEU_PLUS;
			commandu1->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu1);}
		if (selector1 == 2){
			commandu1->unitClicked = UnitClickedType::ATT_PLUS;
			commandu1->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu1);}
//-----------------------------------------------------//
		if (selector2 == 0){
			commandu2->unitClicked = UnitClickedType::DEF_PLUS;
			commandu2->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu2);}
		if (selector2 == 1){
			commandu2->unitClicked = UnitClickedType::NEU_PLUS;
			commandu2->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu2);}
		if (selector2 == 2){
			commandu2->unitClicked = UnitClickedType::ATT_PLUS;
			commandu2->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu2);}
//---------------------------------------------------//
		if (selector3 == 0){
			commandu3->unitClicked = UnitClickedType::DEF_PLUS;
			commandu3->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu3);}
		if (selector3 == 1){
			commandu3->unitClicked = UnitClickedType::NEU_PLUS;
			commandu3->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu3);}
		if (selector3 == 2){
			commandu3->unitClicked = UnitClickedType::ATT_PLUS;
			commandu3->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu3);}
//---------------------------------------------------//
		if (selector4 == 0){
			commandu4->unitClicked = UnitClickedType::DEF_PLUS;
			commandu4->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu4);}
		if (selector4 == 1){
			commandu4->unitClicked = UnitClickedType::NEU_PLUS;
			commandu4->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu4);}
		if (selector4 == 2){
			commandu4->unitClicked = UnitClickedType::ATT_PLUS;
			commandu4->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu4);}

		commandfin->pressedKey = KeyPressed::ENTER;
		engine->commands.push(commandfin);

		std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(engine->gameState->currentAction);

		std::shared_ptr<Command> commandspace = std::make_shared<Command>();
		commandspace->pressedKey = KeyPressed::SPACE_BARRE;
		engine->commands.push(commandspace);
	}
	else if(engine->gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
	{

		//printf("IA MOVMENT----------------------------------------------------\n");
		std::shared_ptr<Player> player = engine->gameState->currentPlayer;
		std::shared_ptr<Command> commandor = std::make_shared<Command>();
		std::shared_ptr<Command> commanddest = std::make_shared<Command>();
		std::shared_ptr<Command> commandu1 = std::make_shared<Command>();
		std::shared_ptr<Command> commandu2 = std::make_shared<Command>();
		std::shared_ptr<Command> commandu3 = std::make_shared<Command>();
		std::shared_ptr<Command> commandu4 = std::make_shared<Command>();
		std::shared_ptr<Command> commandfin = std::make_shared<Command>();

		unsigned int n = player->listOwnedCountry.size();
		
		int originCountry = rand() % n;
		int destCountry = rand() % n;	

		//générer les clicks de l'IA
	
//choix pays origine
		commandor->countryClicked = player->listOwnedCountry[originCountry];
		commandor->unitClicked = UnitClickedType::NONE;
		commandor->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandor);

//choix pays destination
		commanddest->countryClicked = player->listOwnedCountry[destCountry];
		commanddest->unitClicked = UnitClickedType::NONE;
		commanddest->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commanddest);
//choix des unités à deplacer	
	int selector1 = rand() % 3;
	int selector2 = rand() % 3;
	int selector3 = rand() % 3;
	int selector4 = rand() % 3;

	if (selector1 == 0){
			commandu1->unitClicked = UnitClickedType::DEF_PLUS;
			commandu1->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu1);}
		if (selector1 == 1){
			commandu1->unitClicked = UnitClickedType::NEU_PLUS;
			commandu1->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu1);}
		if (selector1 == 2){
			commandu1->unitClicked = UnitClickedType::ATT_PLUS;
			commandu1->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu1);}
//-----------------------------------------------------//
		if (selector2 == 0){
			commandu2->unitClicked = UnitClickedType::DEF_PLUS;
			commandu2->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu2);}
		if (selector2 == 1){
			commandu2->unitClicked = UnitClickedType::NEU_PLUS;
			commandu2->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu2);}
		if (selector2 == 2){
			commandu2->unitClicked = UnitClickedType::ATT_PLUS;
			commandu2->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu2);}
//---------------------------------------------------//
		if (selector3 == 0){
			commandu3->unitClicked = UnitClickedType::DEF_PLUS;
			commandu3->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu3);}
		if (selector3 == 1){
			commandu3->unitClicked = UnitClickedType::NEU_PLUS;
			commandu3->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu3);}
		if (selector3 == 2){
			commandu3->unitClicked = UnitClickedType::ATT_PLUS;
			commandu3->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu3);}
//---------------------------------------------------//
		if (selector4 == 0){
			commandu4->unitClicked = UnitClickedType::DEF_PLUS;
			commandu4->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu4);}
		if (selector4 == 1){
			commandu4->unitClicked = UnitClickedType::NEU_PLUS;
			commandu4->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu4);}
		if (selector4 == 2){
			commandu4->unitClicked = UnitClickedType::ATT_PLUS;
			commandu4->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(commandu4);}

	commandfin->pressedKey = KeyPressed::ENTER;
	engine->commands.push(commandfin);
	return;
	}
}
