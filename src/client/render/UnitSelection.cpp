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
   arrow->sprite.setPosition(sf::Vector2f(posX + 5,posY + 10));
   listGraphicElement.push_back(arrow);


   sf::Texture texture_md;
   arrow_md->texture = texture_md;
   arrow_md->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_md;
   arrow_md->sprite = sprite_arrow_md;
   arrow_md->sprite.setTexture(arrow->texture);
   arrow_md->sprite.setPosition(sf::Vector2f(posX + 500,posY + 10));
   listGraphicElement.push_back(arrow_md);


   sf::Texture texture_rd;
   arrow_rd->texture = texture_rd;
   arrow_rd->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_rd;
   arrow_rd->sprite = sprite_arrow_rd;
   arrow_rd->sprite.setTexture(arrow->texture);
   arrow_rd->sprite.setPosition(sf::Vector2f(posX + 1000,posY + 10));
   listGraphicElement.push_back(arrow_rd);

   float rot=180;
   sf::Texture texture_lu;
   arrow_lu->texture = texture_lu;
   arrow_lu->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_lu;
   arrow_lu->sprite = sprite_arrow_lu;
   arrow_lu->sprite.setTexture(arrow->texture);
   arrow_lu->sprite.setRotation(rot);
   arrow_lu->sprite.setPosition(sf::Vector2f(posX + 5,posY - 10));
   listGraphicElement.push_back(arrow_lu);


   sf::Texture texture_mu;
   arrow_mu->texture = texture_mu;
   arrow_mu->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_mu;
   arrow_mu->sprite = sprite_arrow_mu;
   arrow_mu->sprite.setPosition(sf::Vector2f(posX + 500,posY - 10));
   listGraphicElement.push_back(arrow_mu);


   sf::Texture texture_ru;
   arrow_ru->texture = texture_ru;
   arrow_ru->texture.loadFromImage(image);

   sf::Sprite sprite_arrow_ru;
   arrow_ru->sprite = sprite_arrow_ru;
   arrow_ru->sprite.setPosition(sf::Vector2f(posX + 1000,posY - 10));
   listGraphicElement.push_back(arrow_ru);
   
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
