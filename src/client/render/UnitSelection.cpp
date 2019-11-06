#include "state.h"
#include "UnitSelection.h"
#include <SFML/Graphics.hpp>
#include "../../define.h"
#include <string> 



using namespace state;
using namespace render;

UnitSelection::UnitSelection()
{
   //---------------------------------------//
   // declaration des variables des textures//
   //---------------------------------------//

   float scale = 0.6;
   float posX = 220;
   float posY = 150;
   float arrow_up_offsetY = 40;
   float arrow_down_offsetY = 250;
   float arrow_up_offsetX = 160;
   sf::Image image;
   if (!(image.loadFromFile("../res/unit_textures.png")))
      printf("Cannot load image");
   std::shared_ptr<GraphicElement> unit = std::make_shared<GraphicElement>();

   sf::Texture texture;
   unit->texture = texture;
   unit->texture.loadFromImage(image);	//creation des textures pour GraphicElement

   sf::Sprite sprite;
   unit->sprite = sprite;
   unit->sprite.setTexture(unit->texture);
   unit->sprite.setPosition(sf::Vector2f(posX,posY));

   listGraphicElement.push_back(unit);


   if (!(image.loadFromFile("../res/arrow_down.png")))
      printf("Cannot load image");

   std::shared_ptr<GraphicElement> arrow = std::make_shared<GraphicElement>();
   std::shared_ptr<GraphicElement> arrow_md = std::make_shared<GraphicElement>();
   std::shared_ptr<GraphicElement> arrow_rd = std::make_shared<GraphicElement>();
   std::shared_ptr<GraphicElement> arrow_lu = std::make_shared<GraphicElement>();
   std::shared_ptr<GraphicElement> arrow_mu = std::make_shared<GraphicElement>();
   std::shared_ptr<GraphicElement> arrow_ru = std::make_shared<GraphicElement>();


   sf::Texture texture2;
   arrow->texture = texture2;
   arrow->texture.loadFromImage(image);	//creation des textures pour GraphicElement

   sf::Sprite sprite_arrow_ld;
   arrow->sprite = sprite_arrow_ld;
   arrow->sprite.setTexture(arrow->texture);
   arrow->sprite.setScale(scale,scale);
   arrow->sprite.setPosition(sf::Vector2f(posX +25,posY + arrow_down_offsetY));
   listGraphicElement.push_back(arrow);


   sf::Texture texture_md;
   arrow_md->texture = texture_md;
   arrow_md->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_md;
   arrow_md->sprite = sprite_arrow_md;
   arrow_md->sprite.setTexture(arrow->texture);
   arrow_md->sprite.setScale(scale,scale);
   arrow_md->sprite.setPosition(sf::Vector2f(posX + 300,posY + arrow_down_offsetY));
   listGraphicElement.push_back(arrow_md);


   sf::Texture texture_rd;
   arrow_rd->texture = texture_rd;
   arrow_rd->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_rd;
   arrow_rd->sprite = sprite_arrow_rd;
   arrow_rd->sprite.setTexture(arrow->texture);
   arrow_rd->sprite.setScale(scale,scale);
   arrow_rd->sprite.setPosition(sf::Vector2f(posX + 550,posY + arrow_down_offsetY));
   listGraphicElement.push_back(arrow_rd);


// generer les flèche vers le haut
   float rot=180.;
   sf::Texture texture_lu;
   arrow_lu->texture = texture_lu;
   arrow_lu->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_lu;
   arrow_lu->sprite = sprite_arrow_lu;
   arrow_lu->sprite.setTexture(arrow->texture);
   arrow_lu->sprite.setScale(scale,scale);
   arrow_lu->sprite.setRotation(rot);
   arrow_lu->sprite.setPosition(sf::Vector2f(posX + arrow_up_offsetX + 25,posY + arrow_up_offsetY));
   listGraphicElement.push_back(arrow_lu);

   sf::Texture texture_mu;
   arrow_mu->texture = texture_mu;
   arrow_mu->texture.loadFromImage(image); 

   sf::Sprite sprite_mu;
   arrow_mu->sprite = sprite_mu;
   arrow_mu->sprite.setTexture(arrow->texture);
   arrow_mu->sprite.setRotation(rot);
   arrow_mu->sprite.setScale(scale,scale);
   arrow_mu->sprite.setPosition(sf::Vector2f(posX + arrow_up_offsetX + 300, posY + arrow_up_offsetY));
   listGraphicElement.push_back(arrow_mu); 
   


   sf::Texture texture_ru;
   arrow_ru->texture = texture_ru;
   arrow_ru->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_ru;
   arrow_ru->sprite = sprite_arrow_ru;
   arrow_ru->sprite.setTexture(arrow->texture);
   arrow_ru->sprite.setPosition(sf::Vector2f(posX + arrow_up_offsetX + 550,posY + arrow_up_offsetY));
   arrow_ru->sprite.setRotation(rot);
   arrow_ru->sprite.setScale(scale,scale);
   listGraphicElement.push_back(arrow_ru);




   //importation des fonds 
   if (!(image.loadFromFile("../res/reinforcement.png")))
      printf("Cannot load image");

   std::shared_ptr<GraphicElement> reinforcement_graph = std::make_shared<GraphicElement>();

   sf::Texture texture_rein;
   reinforcement_graph->texture = texture_rein;
   reinforcement_graph->texture.loadFromImage(image);

   sf::Sprite sprite_rein;
   reinforcement_graph->sprite = sprite_rein;
   reinforcement_graph->sprite.setTexture(reinforcement_graph->texture);
   reinforcement_graph->sprite.setPosition(sf::Vector2f(150,0));
   //reinforcement_graph->sprite.setRotation(rot);
   reinforcement_graph->sprite.setScale(1,1);
   listGraphicElement.push_back(reinforcement_graph);

if (!(image.loadFromFile("../res/attaque.png")))
      printf("Cannot load image");

   std::shared_ptr<GraphicElement> attaque_graph = std::make_shared<GraphicElement>();

   sf::Texture texture_att;
   attaque_graph->texture = texture_att;
   attaque_graph->texture.loadFromImage(image);

   sf::Sprite sprite_att;
   attaque_graph->sprite = sprite_att;
   attaque_graph->sprite.setTexture(attaque_graph->texture);
   attaque_graph->sprite.setPosition(sf::Vector2f(150,0));
   //reinforcement_graph->sprite.setRotation(rot);
   attaque_graph->sprite.setScale(1,1);
   listGraphicElement.push_back(attaque_graph);


if (!(image.loadFromFile("../res/movement.png")))
      printf("Cannot load image");

   std::shared_ptr<GraphicElement> movement_graph = std::make_shared<GraphicElement>();

   sf::Texture texture_mov;
   movement_graph->texture = texture_mov;
   movement_graph->texture.loadFromImage(image);

   sf::Sprite sprite_mov;
   movement_graph->sprite = sprite_mov;
   movement_graph->sprite.setTexture(movement_graph->texture);
   movement_graph->sprite.setPosition(sf::Vector2f(150,0));
   //reinforcement_graph->sprite.setRotation(rot);
   movement_graph->sprite.setScale(1,1);
   listGraphicElement.push_back(movement_graph);
   
}














void UnitSelection::Draw(std::shared_ptr<sf::RenderWindow> renderWindow){
	//declaration des variables de position
   float posX = 220;
   float posY = 150;




    if(currentAction->GetActionType() == ActionType::_REINFORCEMENTS){
       std::shared_ptr<Reinforcements> rein = std::dynamic_pointer_cast<Reinforcements>(currentAction);
       if (rein->unitSelected == true)
	{


   	//definir le nombre de chaque type pour chaque territoire
	/*Attack attack=Attack();
   	unsigned int n = attack.attackerUnits.size();

	unsigned int attunits = 0;
	unsigned int neuunits = 0;
	unsigned int defunits = 0;
	   for (unsigned int i = 0; i < n; i++){
	      if(attack.attackerUnits[i]->type == Type::attaquant)
		attunits++;
	      if(attack.attackerUnits[i]->type == Type::neutre)
		neuunits++;
	      if(attack.attackerUnits[i]->type == Type::defensif)
		defunits++;     
	   }
      	std::string str_att = std::to_string(attunits);
        std::string str_neutre = std::to_string(neuunits);
        std::string str_def = std::to_string(defunits);



	//charger la font

	sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("../res/FFF_Tusj.ttf"))
            printf("font not found");*/



	//charger les elements graphiques

       listGraphicElement[7]->DrawElement(renderWindow);
       for (int i = 0; i < 7; i++) {
       listGraphicElement[i]->DrawElement(renderWindow);//load reinforcement sprite and arrows 
       }  



	//afficher le nombre de troupe.
	/*text.setFont(font);
        text.setString(str_def+" "+str_neutre+" "+str_att);
	text.setPosition(posX,posY);
        renderWindow->draw(text); */    
    }
    }




	 //-------//
	 // ATTACK//
	 //-------//

    if(currentAction->GetActionType() == ActionType::_ATTACK)
	{
        std::shared_ptr<Attack> attack = std::dynamic_pointer_cast<Attack>(currentAction);
        if (attack->unitSelected == true)
	{
	//definir le nombre de chaque type impliqué dans l'attaque 
	//Attack attack=Attack();
   	unsigned int n = attack->attackerUnits.size();

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
      	std::string str_att = std::to_string(attunits);
        std::string str_neutre = std::to_string(neuunits);
        std::string str_def = std::to_string(defunits);

	//charger la font

	sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("../res/FFF_Tusj.ttf"))
            printf("font not found");

	//charger les elements graphiques
       listGraphicElement[8]->DrawElement(renderWindow);
       for (int i = 0; i < 7; i++) {
       listGraphicElement[i]->DrawElement(renderWindow);//load reinforcement sprite and arrows 
       }  
    //afficher le nombre de troupe.
	text.setFont(font);
        text.setString(str_def+" "+str_neutre+" "+str_att);
	text.setPosition(posX,posY);
        renderWindow->draw(text);     
    }
    }


	 //---------//
	 // MOVEMENT//
	 //---------//


        if(currentAction->GetActionType() == ActionType::_MOVEMENT)
	{
        std::shared_ptr<Movement> movement = std::dynamic_pointer_cast<Movement>(currentAction);
        if (movement->unitSelected == true)
	{
//definir le nombre de chaque type impliqué dans l'attaque 
	//Movement movement;
   	unsigned int n = movement->units.size();

	unsigned int attunits = 0;
	unsigned int neuunits = 0;
	unsigned int defunits = 0;
	   for (unsigned int i = 0; i < n; i++){
	      if(movement->units[i]->type == Type::attaquant)
		attunits++;
	      if(movement->units[i]->type == Type::neutre)
		neuunits++;
	      if(movement->units[i]->type == Type::defensif)
		defunits++;     
	   }
      	std::string str_att = std::to_string(attunits);
        std::string str_neutre = std::to_string(neuunits);
        std::string str_def = std::to_string(defunits);

	//charger la font

	sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("../res/FFF_Tusj.ttf"))
            printf("font not found");


       listGraphicElement[9]->DrawElement(renderWindow);
       for (int i = 0; i < 7; i++) {
       listGraphicElement[i]->DrawElement(renderWindow);//load reinforcement sprite and arrows 
       } 
//afficher le nombre de troupe.
	text.setFont(font);
        text.setString(str_def+" "+str_neutre+" "+str_att);
	text.setPosition(posX,posY);
        renderWindow->draw(text);      
    }
    }
}


void UnitSelection::Update(std::shared_ptr<sf::RenderWindow> renderWindow){
	Draw(renderWindow);

}
