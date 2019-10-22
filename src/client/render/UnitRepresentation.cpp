#include "state.h"
#include "UnitRepresentation.h"
#include <SFML/Graphics.hpp>
#include "../../define.h"
#include <string> 



using namespace state;
using namespace render;

UnitRepresentation::UnitRepresentation()
{
   
	sf::Image image;
	float tabX[18]={UNIT_POS_X};
	float tabY[18]={UNIT_POS_Y};
   	for (int i = 0; i < NB_COUNTRY; i++) { 
      		if (!(image.loadFromFile("../res/unit_textures.png")))
       			printf("Cannot load image");

		std::shared_ptr<GraphicElement> unit = std::make_shared<GraphicElement>();

		sf::Texture texture;
		unit->texture = texture;
		unit->texture.loadFromImage(image);	//creation des textures pour GraphicElement

		sf::Sprite sprite;
		unit->sprite = sprite;
		unit->sprite.setTexture(unit->texture);	//creation des sprites pour GraphicElement
		printf("%f\n",tabX[i]);
		unit->sprite.setPosition(sf::Vector2f(tabX[i], tabY[i]));
		unit->sprite.setScale(sf::Vector2f(0.1f, 0.1f));
		//unit->sprite.scale(sf::Vector2f(0.1f, 0.1f));
		listGraphicElement.push_back(unit);	//ajouts a listGraphicElements dans layer
	}
}

void UnitRepresentation::Update (std::shared_ptr<sf::RenderWindow> renderWindow){
    for (int i = 0; i < NB_COUNTRY; i++) {
        std::shared_ptr<Country>  country = listCountry[i];

/*definir le nombre de chaque type pour chaque territoire*/
        int nbr_att = country->FindTypeNumber(Type::attaquant);
        int nbr_neutre = country->FindTypeNumber(Type::neutre);
        int nbr_def = country->FindTypeNumber(Type::defensif);
        std::string str_att = std::to_string(nbr_att);
        std::string str_neutre = std::to_string(nbr_neutre);
        std::string str_def = std::to_string(nbr_def);

/*afficher le pays avec le nombre d'unités*/
        listGraphicElement[i]->DrawElement(renderWindow);
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("../res/FFF_Tusj.ttf"))
            printf("font not found");
        text.setFont(font);
        text.setString(str_def+str_neutre+str_att);
        renderWindow->draw(text);
        
    }
}


void UnitRepresentation::Draw (std::shared_ptr<sf::RenderWindow> renderWindow){
    //il faut parcourir la liste des pays pour savoir le nombre d'unitées dessus
    //Country country = gameState->listCountry[0]
    for (int i = 0; i < NB_COUNTRY; i++) { 
         listGraphicElement[i]->DrawElement(renderWindow);}
    
}

