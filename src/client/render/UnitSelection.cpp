#include "state.h"
#include "UnitSelection.h"
#include <SFML/Graphics.hpp>
#include "../../define.h"
#include <string> 



using namespace state;
using namespace render;

UnitSelection::UnitSelection()
{
   float posX = 100;
   float posY = 100;
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

   sf::Texture texture2;
   arrow->texture = texture2;
   arrow->texture.loadFromImage(image);	//creation des textures pour GraphicElement

   sf::Sprite sprite2;
   arrow->sprite = sprite2;
   arrow->sprite.setTexture(arrow->texture);
   arrow->sprite.setPosition(sf::Vector2f(posX + 5,posY + 10));

   listGraphicElement.push_back(arrow);

   arrow->sprite.setPosition(sf::Vector2f(posX + 50,posY + 10));
   listGraphicElement.push_back(arrow);

   arrow->sprite.setPosition(sf::Vector2f(posX + 100,posY + 10));
   listGraphicElement.push_back(arrow);

   float rot=180;
   arrow->sprite.setRotation(rot);
   arrow->sprite.setPosition(sf::Vector2f(posX + 50,posY - 10));
   listGraphicElement.push_back(arrow);

   arrow->sprite.setPosition(sf::Vector2f(posX + 50,posY - 10));
   listGraphicElement.push_back(arrow);

   arrow->sprite.setPosition(sf::Vector2f(posX + 50,posY - 10));
   listGraphicElement.push_back(arrow);
   
}



void UnitSelection::Draw(std::shared_ptr<sf::RenderWindow> renderWindow){
    if(currentAction->GetActionType() == ActionType::_REINFORCEMENTS){
       std::shared_ptr<Reinforcements> rein = std::dynamic_pointer_cast<Reinforcements>(currentAction);
       if (rein->unitSelected == true)
	{
       for (int i = 0; i < 7; i++) {
       listGraphicElement[i]->DrawElement(renderWindow);//load reinforcement sprite and arrows 
       }       
    }
    }
    if(currentAction->GetActionType() == ActionType::_ATTACK)
	{
        std::shared_ptr<Attack> att = std::dynamic_pointer_cast<Attack>(currentAction);
        if (att->unitSelected == true)
	{
       for (int i = 0; i < 7; i++) {
       listGraphicElement[i]->DrawElement(renderWindow);//load reinforcement sprite and arrows 
       }    
    }
    }
        if(currentAction->GetActionType() == ActionType::_MOVEMENT)
	{
        std::shared_ptr<Movement> mov = std::dynamic_pointer_cast<Movement>(currentAction);
        if (mov->unitSelected == true)
	{
       for (int i = 0; i < 7; i++) {
       listGraphicElement[i]->DrawElement(renderWindow);//load reinforcement sprite and arrows 
       }    
    }
    }
}


void UnitSelection::Update(std::shared_ptr<sf::RenderWindow> renderWindow){
	Draw(renderWindow);

}
