#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[])
{
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1267, 628), "Risk");

	//Creation et initialisation d'une scene
	Scene scene;
	std::shared_ptr<WorldMap> worldMap = std::make_shared<WorldMap>();
	std::shared_ptr<UnitRepresentation> unitRepresentation = std::make_shared<UnitRepresentation>();
	std::shared_ptr<GameState> gameState = std::make_shared<GameState>();
	scene.worldMap = worldMap;
	scene.unitRepresentation = unitRepresentation;
	scene.renderWindow = window;
	scene.gameState = gameState;

	

	// run the program as long as the window is open
	while (window->isOpen())
	{
	        // check all the window's events that were triggered since the last iteration of the loop
	        sf::Event event;
	        while (window->pollEvent(event))
	        {
        		// "close requested" event: we close the window
        		if (event.type == sf::Event::Closed)
                	window->close();
        	}
	
	scene.Draw();
	window->display();
    }
    
   return 0;
   
}
