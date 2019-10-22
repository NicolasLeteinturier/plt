#include "state.h"
#include "WorldMap.h"
#include <SFML/Graphics.hpp>

using namespace state;
using namespace render;

WorldMap::WorldMap()
{
	// Chargement des images	
	sf::Image image;
   	int number_cntry=18;
   	char table[number_cntry][40]={"../res/Map_Argentina.png","../res/Map_Asia_Est.png","../res/Map_Asia_North.png","../res/Map_Asia_South.png","../res/Map_Asia_West.png","../res/Map_Brazil.png","../res/Map_Central_africa.png","../res/Map_Europe_Est.png","../res/Map_Europe_North.png","../res/Map_Europe_West.png","../res/Map_North_africa.png","../res/Map_North_America.png","../res/Map_Oceania_Est.png","../res/Map_Oceania_North.png","../res/Map_Oceania_West.png","../res/Map_Orient.png","../res/Map_South_africa.png","../res/Map_USA.png"};
   	for (int i = 0; i < number_cntry; i++) { 
      		if (!(image.loadFromFile(table[i])))
          	    printf("Cannot load image");
		images.push_back(image);//mise en memoir du vecteur d'image pour WorldMap


		std::shared_ptr<GraphicElement> pays1 = std::make_shared<GraphicElement>();
		sf::Texture texture1;
	       texture1.loadFromImage(image);//creation des textures pour GraphicElement
	       sf::Sprite sprite1;
	       sprite1.setTexture(texture1);//creation des sprites pour GraphicElement
		pays1->sprite = sprite1;
		pays1->texture = texture1;
		listGraphicElement.push_back(pays1);//ajouts a listGraphicElements dans layer

}



}



void WorldMap::Draw(std::shared_ptr<sf::RenderWindow> renderWindow)
{
   //sf::Image image;
   int number_cntry=18;
   //char table[number_cntry][40]={"../res/Map_Argentina.png","../res/Map_Asia_Est.png","../res/Map_Asia_North.png","../res/Map_Asia_South.png","../res/Map_Asia_West.png","../res/Map_Brazil.png","../res/Map_Central_africa.png","../res/Map_Europe_Est.png","../res/Map_Europe_North.png","../res/Map_Europe_West.png","../res/Map_North_africa.png","../res/Map_North_America.png","../res/Map_Oceania_Est.png","../res/Map_Oceania_North.png","../res/Map_Oceania_West.png","../res/Map_Orient.png","../res/Map_South_africa.png","../res/Map_USA.png"};
   for (int i = 0; i < number_cntry; i++) { 
      /*if (!(image.loadFromFile(table[i])))
          printf("Cannot load image");
       sf::Texture texture;
       texture.loadFromImage(image);
       sf::Sprite sprite;
       sprite.setTexture(texture);
   
       renderWindow->draw(sprite);
       renderWindow->display();*/
	listGraphicElement[i]->DrawElement(renderWindow);
	//renderWindow->display();
   }
}
   

void WorldMap::Update (){
}

