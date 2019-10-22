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

        //Initialisation des joueurs
        std::shared_ptr<Player> Player1 = std::make_shared<Player>();
        std::shared_ptr<Player> Player2 = std::make_shared<Player>();

        Player1->id = "joueur 1";
        Player2->id = "joueur 2";
        gameState->AddPlayer(Player1);
        gameState->AddPlayer(Player2);



	std::shared_ptr<Initialisation> init = std::dynamic_pointer_cast<Initialisation>(gameState->currentAction);
        init->EndInitialisation();

	worldMap->listCountry = gameState->listCountry;
	unitRepresentation->listCountry = gameState->listCountry;

	scene.worldMap = worldMap;
	scene.unitRepresentation = unitRepresentation;
	scene.renderWindow = window;
	scene.gameState = gameState;


	sf::Image image;
	if (!(image.loadFromFile("../res/font.png")))
          		printf("Cannot load image");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
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
	window->draw(sprite);
	scene.Draw();
        scene.Update();
	window->display();
    }
    
   return 0;
   
}
