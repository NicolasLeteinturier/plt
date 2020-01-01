#include "../../shared/state.h"
#include "Scene.h"


using namespace state;
using namespace render;

Scene::Scene()
{
}

Scene::Scene(std::shared_ptr<GameState> _gameState)
{
		printf("\tcheck pointeur scene\n");
	std::shared_ptr<WorldMap> _worldMap = std::make_shared<WorldMap>();
	std::shared_ptr<UnitRepresentation> _unitRepresentation = std::make_shared<UnitRepresentation>();
        std::shared_ptr<UnitSelection> _unitSelection = std::make_shared<UnitSelection>();
	std::shared_ptr<AttackDisplay> _attackDisplay = std::make_shared<AttackDisplay>();

	printf("\tcheck Listcountry scene\n");
	_worldMap->listCountry = _gameState->listCountry;
	_unitRepresentation->listCountry = _gameState->listCountry;
        _unitSelection->listCountry = _gameState->listCountry;
	_attackDisplay->listCountry = _gameState->listCountry;

	printf("\tcheck Worldmap scene\n");
	worldMap = _worldMap;
	printf("\tcheck Unitrepresentation scene\n");
	unitRepresentation = _unitRepresentation;
	printf("\tcheck unitSelection scene\n");
        unitSelection = _unitSelection;
	printf("\tcheck attackDisplay scene\n");
	attackDisplay = _attackDisplay;
	printf("\tcheck gamestate scene\n");
	gameState = _gameState;
	printf("\tend scene\n");

	return;
}

void Scene::Draw()
{

	worldMap->listCountry = gameState->listCountry;
	unitRepresentation->listCountry = gameState->listCountry;
        unitSelection->listCountry = gameState->listCountry;
	attackDisplay->listCountry = gameState->listCountry;

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

	worldMap->listCountry = gameState->listCountry;
	unitRepresentation->listCountry = gameState->listCountry;
        unitSelection->listCountry = gameState->listCountry;
	attackDisplay->listCountry = gameState->listCountry;

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

