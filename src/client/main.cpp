#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
	printf("arriver ici");
	std::shared_ptr<sf::RenderWindow> renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1370,720), "menu test");
	cout << "It works !" << endl;
	return 0;
}
