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
	/*printf("arriver ici");
	std::shared_ptr<sf::RenderWindow> renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1370,720), "menu test");
	cout << "It works !" << endl;
	return 0;*/

   std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1350, 720), "My window");
    WorldMap * map = new WorldMap();
    GraphicElement pays;
    
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
	
	Layer layer;
	sf::Texture pays=layer.listGraphicElement[0]->texture;
	sf::Sprite sprite1;
	sprite1.setTexture(pays);
	window->draw(sprite1);
	window->display();
    }
    
   return 0;
   
}
