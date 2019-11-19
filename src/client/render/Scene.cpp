#include "../../shared/state.h"
#include "Scene.h"


using namespace state;
using namespace render;

Scene::Scene()
{
}

void Scene::Draw()
{
	worldMap->Draw(renderWindow);
	unitRepresentation->Draw(renderWindow);
        //unitSelection->Draw(renderWindow);
	if(gameState->currentAction->GetActionType()==ActionType::_ATTACK)
	{
		std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(gameState->currentAction);
		attackDisplay->attack = attack;
		attackDisplay->Draw(renderWindow);
	}
	return;
}

void Scene::Update()
{
	//worldMap->Update();
	unitRepresentation->Update(renderWindow);
	unitSelection->currentAction = gameState->currentAction;
        unitSelection->Update(renderWindow);
	if(gameState->currentAction->GetActionType()==ActionType::_ATTACK)
	{
		std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(gameState->currentAction);
		attackDisplay->attack = attack;
		attackDisplay->Update(renderWindow);
	}
	return;
}

