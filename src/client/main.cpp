#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include "render/WorldMap.h"

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[])
{
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1267, 628), "Risk");
   
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
	
	WorldMap * worldMap = new WorldMap();
	sf::Texture pays=worldMap->listGraphicElement[0]->texture;
	sf::Sprite sprite1;
	sprite1.setTexture(pays);
	window->draw(sprite1);
	window->display();
    }
    
   return 0;
   
}
