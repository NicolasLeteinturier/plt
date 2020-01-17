#include "state.h"
#include "AttackDisplay.h"
#include <SFML/Graphics.hpp>
#include "../../define.h"
#include <string> 
using namespace render;
using namespace state;



AttackDisplay::AttackDisplay()
{

   //---------------------------------------//
   // declaration des variables des textures//
   //---------------------------------------//

int sizeX = 1227;
//int sizeY = 628;

//int unitOffsetX =220;
int unitTopOffsetY =20;

int unitBotOffsetY =500;

int winPosX =150;



sf::Image image;

if (!(image.loadFromFile("../res/attaque.png")))
      printf("Cannot load image");

   std::shared_ptr<GraphicElement> attaque_graph = std::make_shared<GraphicElement>();

   sf::Texture texture_att;
   attaque_graph->texture = texture_att;
   attaque_graph->texture.loadFromImage(image);

   sf::Sprite sprite_att;
   attaque_graph->sprite = sprite_att;
   attaque_graph->sprite.setTexture(attaque_graph->texture);
   attaque_graph->sprite.setPosition(sf::Vector2f(winPosX,0));
   attaque_graph->sprite.setScale(1,1);
   listGraphicElement.push_back(attaque_graph);


if (!(image.loadFromFile("../res/unit_textures.png")))
      printf("Cannot load image");
   std::shared_ptr<GraphicElement> unit1 = std::make_shared<GraphicElement>();

   sf::Texture texture;
   unit1->texture = texture;
   unit1->texture.loadFromImage(image);	//creation des textures pour GraphicElement

   sf::Sprite sprite1;
   unit1->sprite = sprite1;
   unit1->sprite.setTexture(unit1->texture);
   unit1->sprite.setPosition(sf::Vector2f(sizeX/2-150,unitTopOffsetY));
   unit1->sprite.setScale(0.5,0.5);

   listGraphicElement.push_back(unit1);


if (!(image.loadFromFile("../res/unit_textures.png")))
      printf("Cannot load image");
   std::shared_ptr<GraphicElement> unit2 = std::make_shared<GraphicElement>();

   sf::Texture texture2;
   unit2->texture = texture2;
   unit2->texture.loadFromImage(image);	//creation des textures pour GraphicElement

   sf::Sprite sprite2;
   unit2->sprite = sprite2;
   unit2->sprite.setTexture(unit2->texture);
   unit2->sprite.setPosition(sf::Vector2f(sizeX/2-150,unitBotOffsetY));
   unit2->sprite.setScale(0.5,0.5);

   listGraphicElement.push_back(unit2);





}

void AttackDisplay::Draw(std::shared_ptr<sf::RenderWindow> renderWindow){

	if (attack->displayAttack){
   //---------------------------------------//
   // declaration des variables des textures//
   //---------------------------------------//
	sf::Color colorTable[4] = {COLOR_TABLE};
	int sizeX = 1227;
	//unsigned int sizeY = 628;

	//unsigned int unitOffsetX =220;
	unsigned int unitTopOffsetY =20;

	unsigned int unitBotOffsetY =450;

	//unsigned int winPosX =150;

	//---------//
	//graphique//
	//---------//

	listGraphicElement[0]->DrawElement(renderWindow);
	listGraphicElement[1]->DrawElement(renderWindow);
	listGraphicElement[2]->DrawElement(renderWindow);


	//------------------------------------------//
        //afficher les nombre d'unité pays attaquant//
	//------------------------------------------//


	unsigned int n = attack->attackerUnits.size();

	unsigned int attCmpt = 0;

	unsigned int attunits = 0;
	unsigned int neuunits = 0;
	unsigned int defunits = 0;
	   for (unsigned int i = 0; i < n; i++){
	      if(attack->attackerUnits[i]->type == Type::attaquant)
		attunits++;
	      if(attack->attackerUnits[i]->type == Type::neutre)
		neuunits++;
	      if(attack->attackerUnits[i]->type == Type::defensif)
		defunits++;     
	   }
	attCmpt = attunits + neuunits + defunits;
      	std::string str_att = std::to_string(attunits);
        std::string str_neutre = std::to_string(neuunits);
        std::string str_def = std::to_string(defunits);

	//charger la font

	sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("../res/FFF_Tusj.ttf"))
            printf("font not found");
        text.setFont(font);
        text.setString(str_def+"   "+str_neutre+"   "+str_att);
	text.setPosition(sizeX/2-120,unitTopOffsetY+10);
	text.setFillColor(colorTable[attack->attackerCountry->owner->color]);
        text.setScale(3,3);
        renderWindow->draw(text); 



 //------------------------------------------//
 //afficher les nombre d'unité pays defenceur//
 //------------------------------------------//
	unsigned int nd = attack->defencerUnits.size();

	unsigned int defCmpt = 0;

	unsigned int attunits2 = 0;
	unsigned int neuunits2 = 0;
	unsigned int defunits2 = 0;
	   for (unsigned int i = 0; i < nd; i++){
	      if(attack->defencerUnits[i]->type == Type::attaquant)
		attunits2++;
	      if(attack->defencerUnits[i]->type == Type::neutre)
		neuunits2++;
	      if(attack->defencerUnits[i]->type == Type::defensif)
		defunits2++;     
	   }
        defCmpt = attunits2 + neuunits2 + defunits2;
      	std::string str_att2 = std::to_string(attunits2);
        std::string str_neutre2 = std::to_string(neuunits2);
        std::string str_def2 = std::to_string(defunits2);

	//charger la font

	sf::Text text2;
        if (!font.loadFromFile("../res/FFF_Tusj.ttf"))
            printf("font not found");
        text2.setFont(font);
        text2.setString(str_def2+"   "+str_neutre2+"   "+str_att2);
	text2.setPosition(sizeX/2-120,unitBotOffsetY+50);
	text2.setFillColor(colorTable[attack->defencerCountry->owner->color]);
        text2.setScale(3,3);
        renderWindow->draw(text2);



	//--------------------------------------------------//
	//definir les deux rectangles représentant le combat//
	//--------------------------------------------------// 
	int width = 400;
	int Yoffset = 300;
	float rectPosX = (sizeX/2)-(width/2);

	float sizeAtt= attCmpt*(667-Yoffset)/(attCmpt + defCmpt + 1);





        sf::RectangleShape rectangleTop;
	rectangleTop.setSize(sf::Vector2f(width, sizeAtt));
	rectangleTop.setOutlineColor(sf::Color::Red);
	rectangleTop.setFillColor(colorTable[attack->attackerCountry->owner->color]);
	rectangleTop.setPosition(rectPosX, Yoffset/2);//////////////////////////////

	float sizeDef= defCmpt*(667-Yoffset)/(attCmpt + defCmpt);

        sf::RectangleShape rectangleBot;
	rectangleBot.setSize(sf::Vector2f(width, sizeDef));
	rectangleBot.setOutlineColor(sf::Color::Green);
	rectangleBot.setFillColor(colorTable[attack->defencerCountry->owner->color]);
	rectangleBot.setPosition(rectPosX, Yoffset/2+sizeAtt+5);//////////////////////////////
	renderWindow->draw(rectangleTop);
	renderWindow->draw(rectangleBot);
}

	return;

}



void AttackDisplay::Update(std::shared_ptr<sf::RenderWindow> renderWindow){
	Draw(renderWindow);

}







   









