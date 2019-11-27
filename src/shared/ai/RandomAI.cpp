#include <queue>
#include "RandomAI.h"
#include <stdlib.h>
#include "../../define.h"

using namespace ai;
using namespace state;
using namespace engine;

RandomAI::RandomAI()
{
}


void RandomAI::play()
{
	/*variables Globales*/
        float tabX[NB_COUNTRY]={UNIT_POS_X};
        float tabY[NB_COUNTRY]={UNIT_POS_Y};		
	
	if(engine->gameState->currentPlayer->isAnIA == false)
	{
		return;
	}	
	if(engine->gameState->currentAction->GetActionType() == ActionType::_INITIALISATION)
	{

	}
	else if(engine->gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
	{
		engine->gameState->GoToNextAction();
	}
	else if(engine->gameState->currentAction->GetActionType() == ActionType::_ATTACK)
	{
		engine->gameState->GoToNextAction();
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
		unsigned int i=0;
		for(i=0;i<engine->gameState->listCountry.size();i++){
			if (engine->gameState->listCountry[i] == player->listOwnedCountry[originCountry]){
				commandor->mousePositionX = tabX[i];	
				commandor->mousePositionY = tabY[i];
				commandor->pressedKey = KeyPressed::LEFT_CLICK;
				engine->commands.push(commandor);
			}
		}

//choix pays destination
		for(i=0;i<engine->gameState->listCountry.size();i++){

			if (engine->gameState->listCountry[i] == player->listOwnedCountry[destCountry]){
				commanddest->mousePositionX = tabX[i];	
				commanddest->mousePositionY = tabY[i];
				commanddest->pressedKey = KeyPressed::LEFT_CLICK;
				engine->commands.push(commanddest);
			}
		}
//choix des unités à deplacer	
	int selector1 = rand() % 3;
	int selector2 = rand() % 3;
	int selector3 = rand() % 3;
	int selector4 = rand() % 3;

	if (selector1 == 0){
		commandu1->mousePositionX = 300;	
		commandu1->mousePositionY = 130;
		commandu1->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu1);}
	if (selector1 == 1){
		commandu1->mousePositionX =  600;	
		commandu1->mousePositionY =  130;
		commandu1->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu1);}
	if (selector1 == 2){
		commandu1->mousePositionX =  800;	
		commandu1->mousePositionY =  130;
		commandu1->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu1);}
//-----------------------------------------------------//
	if (selector2 == 0){
		commandu2->mousePositionX =  300;	
		commandu2->mousePositionY =  130;
		commandu2->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu2);}
	if (selector2 == 1){
		commandu2->mousePositionX =  600;	
		commandu2->mousePositionY =  130;
		commandu2->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu2);}
	if (selector2 == 2){
		commandu2->mousePositionX =  800;	
		commandu2->mousePositionY =  130;
		commandu2->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu2);}
//---------------------------------------------------//
	if (selector3 == 0){
		commandu3->mousePositionX =  300;	
		commandu3->mousePositionY =  130;
		commandu3->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu3);}
	if (selector3 == 1){
		commandu3->mousePositionX =  600;	
		commandu3->mousePositionY =  130;
		commandu3->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu3);}
	if (selector3 == 2){
		commandu3->mousePositionX =  800;	
		commandu3->mousePositionY =  130;
		commandu3->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu3);}
//---------------------------------------------------//
	if (selector4 == 0){
		commandu4->mousePositionX =  300;	
		commandu4->mousePositionY =  130;
		commandu4->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu4);}
	if (selector4 == 1){
		commandu4->mousePositionX =  600;	
		commandu4->mousePositionY =  130;
		commandu4->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu4);}
	if (selector4 == 2){
		commandu4->mousePositionX =  800;	
		commandu4->mousePositionY =  130;
		commandu4->pressedKey = KeyPressed::LEFT_CLICK;
		engine->commands.push(commandu4);}

	commandfin->pressedKey = KeyPressed::ENTER;
	engine->commands.push(commandfin);
	return;

		
		


		
	}
}
