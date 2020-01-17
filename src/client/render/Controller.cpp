#include <queue>
#include "Controller.h"
#include "../../define.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace render;
using namespace engine;

Controller::Controller()
{
}

void Controller::CheckUserCommand(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			newCommand->pressedKey = KeyPressed::SPACE_BARRE;
			engine->commands.push(newCommand);
			return;
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			newCommand->pressedKey = KeyPressed::ENTER;
			engine->commands.push(newCommand);
			return;
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			newCommand->pressedKey = KeyPressed::ESCAPE;
			engine->commands.push(newCommand);
			return;
		}		
	}

	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			int t = GetCountryClicked(sf::Mouse::getPosition(*(renderWindow)).x,sf::Mouse::getPosition(*(renderWindow)).y);
			if(t == -1 && GetUnitClicked(sf::Mouse::getPosition(*(renderWindow)).x,sf::Mouse::getPosition(*(renderWindow)).y) == UnitClickedType::NONE)
				return;			
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			if(t == -1)
				newCommand->countryClicked = NULL;
			else
				newCommand->countryClicked = engine->gameState->listCountry[t];
			newCommand->unitClicked = GetUnitClicked(sf::Mouse::getPosition(*(renderWindow)).x,sf::Mouse::getPosition(*(renderWindow)).y);
			newCommand->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(newCommand);
			return;
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			int t = GetCountryClicked(sf::Mouse::getPosition(*(renderWindow)).x,sf::Mouse::getPosition(*(renderWindow)).y);
			if(t == -1 && GetUnitClicked(sf::Mouse::getPosition(*(renderWindow)).x,sf::Mouse::getPosition(*(renderWindow)).y) == UnitClickedType::NONE)
				return;			
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			if(t == -1)
				newCommand->countryClicked = NULL;
			else
				newCommand->countryClicked = engine->gameState->listCountry[t];
			newCommand->unitClicked = GetUnitClicked(sf::Mouse::getPosition(*(renderWindow)).x,sf::Mouse::getPosition(*(renderWindow)).y);
			newCommand->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(newCommand);
			return;
		}
	}
	return;
}


int Controller::GetCountryClicked(unsigned int mousePositionX, unsigned int mousePositionY)
{
	sf::Image image;
	char table[NB_COUNTRY][40] = {COUNTRY_SPRITE_RESSOURCES};
	char country_name[NB_COUNTRY][40] = {COUNTRY_NAME};
	for (int i = 0; i < NB_COUNTRY; i++) { 
		if (!(image.loadFromFile(table[i])))
          		printf("Cannot load image");
		if(image.getPixel(mousePositionX,mousePositionY) != sf::Color::Transparent)
		{
			std::cout << country_name[i] << std::endl;
			return(i);
		}
	}
	return(-1);
}

UnitClickedType Controller::GetUnitClicked(unsigned int mousePositionX, unsigned int mousePositionY)
{
	
	if(mousePositionX <= 405 && mousePositionX >= 245)
	{
		if(mousePositionY <= 190 && mousePositionY >= 90)
		{
			return(UnitClickedType::DEF_PLUS);
		}
		else if(mousePositionY <= 500 && mousePositionY >= 400)
		{
			return(UnitClickedType::DEF_MOINS);
		}
		else {return(UnitClickedType::NONE);}
	}

	else if(mousePositionX <= 680 && mousePositionX >= 520)
	{
		if(mousePositionY <= 190 && mousePositionY >= 90)
		{
			return(UnitClickedType::NEU_PLUS);
		}
		else if(mousePositionY <= 500 && mousePositionY >= 400)
		{
			return(UnitClickedType::NEU_MOINS);
		}
		else {return(UnitClickedType::NONE);}
	}

	else if(mousePositionX <= 930 && mousePositionX >= 770)
	{
		if(mousePositionY <= 190 && mousePositionY >= 90)
		{
			return(UnitClickedType::ATT_PLUS);
		}
		else if(mousePositionY <= 500 && mousePositionY >= 400)
		{
			return(UnitClickedType::ATT_MOINS);
		}
		else {return(UnitClickedType::NONE);}
	}
	
}
