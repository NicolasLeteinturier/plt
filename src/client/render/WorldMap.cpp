#include "state.h"
#include "WorldMap.h"
#include <SFML/Graphics.hpp>
#include "../../define.h"

using namespace state;
using namespace render;

WorldMap::WorldMap()
{
	// Chargement des images	
	sf::Image image;

	char table[NB_COUNTRY][40] = {COUNTRY_SPRITE_RESSOURCES};
	
   	for (int i = 0; i < NB_COUNTRY; i++) { 
      		if (!(image.loadFromFile(table[i])))
          		printf("Cannot load image");
		images.push_back(image);//mise en memoire du vecteur d'image pour WorldMap

		std::shared_ptr<GraphicElement> pays = std::make_shared<GraphicElement>();

		sf::Texture texture;
		pays->texture = texture;
		pays->texture.loadFromImage(image);	//creation des textures pour GraphicElement

		sf::Sprite sprite;
		pays->sprite = sprite;
		pays->sprite.setTexture(pays->texture);	//creation des sprites pour GraphicElement
		listGraphicElement.push_back(pays);	//ajouts a listGraphicElements dans layer
	}
}



void WorldMap::Draw(std::shared_ptr<sf::RenderWindow> renderWindow)
{
	for (int i = 0; i < NB_COUNTRY; i++) {
		if(listCountry[i]->owner->id == "joueur 1")
			listGraphicElement[i]->SetElementColor(sf::Color::Red);
		if(listCountry[i]->owner->id == "joueur 2")
			listGraphicElement[i]->SetElementColor(sf::Color::Blue);
		listGraphicElement[i]->DrawElement(renderWindow);
   }
}
   

void WorldMap::Update (std::shared_ptr<sf::RenderWindow> renderWindow){
}

