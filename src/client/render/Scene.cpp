#include "../../shared/state.h"
#include "Scene.h"


using namespace state;
using namespace render;

Scene::Scene()
{
}

Scene::Scene(std::shared_ptr<GameState> _gameState)
{
	std::shared_ptr<WorldMap> _worldMap = std::make_shared<WorldMap>();
	std::shared_ptr<UnitRepresentation> _unitRepresentation = std::make_shared<UnitRepresentation>();
        std::shared_ptr<UnitSelection> _unitSelection = std::make_shared<UnitSelection>();
	std::shared_ptr<AttackDisplay> _attackDisplay = std::make_shared<AttackDisplay>();

	_worldMap->listCountry = _gameState->listCountry;
	_unitRepresentation->listCountry = _gameState->listCountry;
        _unitSelection->listCountry = _gameState->listCountry;
	_attackDisplay->listCountry = _gameState->listCountry;

	worldMap = _worldMap;
	unitRepresentation = _unitRepresentation;
        unitSelection = _unitSelection;
	attackDisplay = _attackDisplay;
	gameState = _gameState;

	return;
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

