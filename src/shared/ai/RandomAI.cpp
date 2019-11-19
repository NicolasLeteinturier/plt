#include <queue>
#include "RandomAI.h"

using namespace ai;
using namespace state;
using namespace engine;

RandomAI::RandomAI()
{
}


void RandomAI::play()
{
	if(engine->gameState->currentPlayer->isAnIA == false)
	{
		return;
	}	
	if(engine->gameState->currentAction->GetActionType() == ActionType::_INITIALISATION)
	{

	}
	else if(engine->gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
	{

	}
	else if(engine->gameState->currentAction->GetActionType() == ActionType::_ATTACK)
	{

	}
	else if(engine->gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
	{

	}
}
