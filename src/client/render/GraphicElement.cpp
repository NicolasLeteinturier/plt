#include "state.h"
#include "GraphicElement.h"
#include <SFML/Graphics.hpp>

using namespace state;
using namespace render;

GraphicElement::GraphicElement()
{
}



void GraphicElement::DrawElement (std::shared_ptr<sf::RenderWindow> renderWindow){
    renderWindow->draw(sprite);
}

void GraphicElement::SetElementColor (sf::Color color){
    sprite.setColor(color);
}

void GraphicElement::SetLocation (int x, int y){
}

