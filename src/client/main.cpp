#include <iostream>
#include <thread>
#include <mutex>

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
#include "ai.h"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

int compteur = 0;
std::mutex mutex1;
std::mutex mutex2;

int main(int argc,char* argv[])
{
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1267, 628), "Risk");
	std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
	std::shared_ptr<GameState> gameState = std::make_shared<GameState>();
	std::shared_ptr<GameState> gameState_testCopy = std::make_shared<GameState>();
	Scene scene(gameState);
	Controller controler;
	HeuristicAI ai;
	RandomAI ai2;
	DeepAI ai3;

	//Creation et initialisation d'une scene
	
	scene.renderWindow = window;

	gameEngine->gameState = gameState;
	gameEngine->JSONActive = true;	

	controler.renderWindow = window;
	controler.engine = gameEngine;

	ai.engine = gameEngine;
	ai2.engine = gameEngine;
	ai3.engine = gameEngine;

        gameState->AddPlayer(IAType::HEURISTIC,"Joueur 1");
        gameState->AddPlayer(IAType::HEURISTIC, "IA 1");
        gameState->AddPlayer(IAType::HEURISTIC, "IA 2");
        gameState->AddPlayer(IAType::HEURISTIC, "IA 3");

	for(unsigned int i = 0; i < 101; i++)
		gameState->GoToNextAction();

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

	/*std::thread engine_thread([gameEngine](){
		while(1)
		{
			mutex1.lock();
			gameEngine->ExecuteCommands();
			mutex1.unlock();
		}
	})*/

	/*std::thread ai_thread([&ai,&ai2,&ai3,&scene,gameEngine](){
		while(1)
		{
			mutex1.lock();
			if(gameEngine->gameState->currentPlayer->isAnIA == IAType::HEURISTIC)
			{
				ai.play();
			}
			else if(gameEngine->gameState->currentPlayer->isAnIA == IAType::RANDOM)
			{
				ai2.play();
			}
			else if(gameEngine->gameState->currentPlayer->isAnIA == IAType::DEEP)
			{
				ai3.play();
				scene.gameState = gameEngine->gameState;
			}
			mutex1.unlock();
		}
	});*/

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
		window->draw(sprite);
		
		scene.Draw();
        	scene.Update();

		if(gameState->listPlayer.size() > 1)
		{
			ai.play();
			ai2.play();
			ai3.play();
			scene.gameState = gameEngine->gameState;
			gameEngine->ExecuteCommands();
		}
		else
		{
			gameEngine->Rollback();
			scene.gameState = gameEngine->gameState;
		}

		std::string curact;
		if(gameEngine->gameState->currentAction->GetActionType() == ActionType::_MOVEMENT)
			curact = "Movement ";
		else if(gameEngine->gameState->currentAction->GetActionType() == ActionType::_REINFORCEMENTS)
			curact = "Reinforcement ";
		else if(gameEngine->gameState->currentAction->GetActionType() == ActionType::_ATTACK)
			curact = "Attack ";
		curact += gameEngine->gameState->currentPlayer->id;


		if (!font.loadFromFile("../res/FFF_Tusj.ttf"))
			    printf("font not found");
		textMov.setFont(font);
		textMov.setString(curact);
		textMov.setPosition(10,10);
		textMov.setFillColor(colorTable[gameEngine->gameState->currentPlayer->color]);
		window->draw(textMov);

		window->display();


	}

	/*engine_thread.join();
	ai_thread.join();*/

	return 0;
   
}
