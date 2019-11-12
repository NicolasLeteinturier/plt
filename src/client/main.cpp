#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <queue>
#include <state.h>
#include "../define.h"
#include "render.h"
#include "engine.h"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;

int compteur = 0;

int main(int argc,char* argv[])
{
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1267, 628), "Risk");

	//Creation et initialisation d'une scene
	Scene scene;
	std::shared_ptr<WorldMap> worldMap = std::make_shared<WorldMap>();
	std::shared_ptr<UnitRepresentation> unitRepresentation = std::make_shared<UnitRepresentation>();
	std::shared_ptr<GameState> gameState = std::make_shared<GameState>();
        std::shared_ptr<UnitSelection> unitSelection = std::make_shared<UnitSelection>();

        //Initialisation des joueurs
        std::shared_ptr<Player> Player1 = std::make_shared<Player>();
        std::shared_ptr<Player> Player2 = std::make_shared<Player>();
        std::shared_ptr<Player> Player3 = std::make_shared<Player>();
        std::shared_ptr<Player> Player4 = std::make_shared<Player>();

        Player1->id = "joueur 1";
        Player2->id = "joueur 2";
        Player3->id = "joueur 3";
        Player4->id = "joueur 4";
        
	Player1->color = 0;
	Player2->color = 1;
	Player3->color = 2;
	Player4->color = 3;

	Player1->isAnIA = false;
	Player2->isAnIA = false;
	Player3->isAnIA = false;
	Player4->isAnIA = false;

	

        gameState->AddPlayer(Player1);
        gameState->AddPlayer(Player2);
        gameState->AddPlayer(Player3);
        gameState->AddPlayer(Player4);

	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();
	gameState->GoToNextAction();


	worldMap->listCountry = gameState->listCountry;
	unitRepresentation->listCountry = gameState->listCountry;
        unitSelection->listCountry = gameState->listCountry;

	scene.worldMap = worldMap;
	scene.unitRepresentation = unitRepresentation;
	scene.renderWindow = window;
	scene.gameState = gameState;
        scene.unitSelection = unitSelection;

	std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();

	gameEngine->gameState = gameState;	

	Controller controler;
	controler.renderWindow = window;
	controler.engine = gameEngine;

	sf::Text textMov;
	sf::Font font;

	sf::Image image;
	if (!(image.loadFromFile("../res/font.png")))
          		printf("Cannot load image");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	// run the program as long as the window is open

	sf::Color colorTable[4] = {COLOR_TABLE};


	while (window->isOpen())
	{
	        // check all the window's events that were triggered since the last iteration of the loop
 		
	        sf::Event event;
	        while (window->pollEvent(event))
	        {
			controler.CheckUserCommand(event);
        		// "close requested" event: we close the window
        		if (event.type == sf::Event::Closed)
                	window->close();
        	}
	


	window->clear();
	gameEngine->ExecuteCommands();
	window->draw(sprite);
	scene.Draw();
        scene.Update();


	std::string curact;
if(gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
		curact = "Movement" + gameState->currentPlayer->id;
	if(gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
		curact = "Reinforcement" + gameState->currentPlayer->id;
	if(gameState->currentAction->GetActionType() == ActionType::_ATTACK)
		curact = "Attack" + gameState->currentPlayer->id;



	if (!font.loadFromFile("../res/FFF_Tusj.ttf"))
		    printf("font not found");
	textMov.setFont(font);
	textMov.setString(curact);
	textMov.setPosition(10,10);
	textMov.setFillColor(colorTable[gameState->currentPlayer->color]);
	window->draw(textMov);
	window->display();


    }
    
   return 0;
   
}
