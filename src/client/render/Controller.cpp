#include <queue>
#include "Controller.h"

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
			newCommand->mousePositionX = sf::Mouse::getPosition(*(renderWindow)).x;
			newCommand->mousePositionY = sf::Mouse::getPosition(*(renderWindow)).y;
			newCommand->pressedKey = KeyPressed::SPACE_BARRE;
			engine->commands.push(newCommand);
			return;
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			newCommand->mousePositionX = sf::Mouse::getPosition(*(renderWindow)).x;
			newCommand->mousePositionY = sf::Mouse::getPosition(*(renderWindow)).y;
			newCommand->pressedKey = KeyPressed::ENTER;
			engine->commands.push(newCommand);
			return;
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			newCommand->mousePositionX = sf::Mouse::getPosition(*(renderWindow)).x;
			newCommand->mousePositionY = sf::Mouse::getPosition(*(renderWindow)).y;
			newCommand->pressedKey = KeyPressed::ESCAPE;
			engine->commands.push(newCommand);
			return;
		}		
	}

	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			newCommand->mousePositionX = sf::Mouse::getPosition(*(renderWindow)).x;
			newCommand->mousePositionY = sf::Mouse::getPosition(*(renderWindow)).y;
			newCommand->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(newCommand);
			return;
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			std::shared_ptr<Command> newCommand = std::make_shared<Command>();
			newCommand->mousePositionX = sf::Mouse::getPosition(*(renderWindow)).x;
			newCommand->mousePositionY = sf::Mouse::getPosition(*(renderWindow)).y;
			newCommand->pressedKey = KeyPressed::LEFT_CLICK;
			engine->commands.push(newCommand);
			return;
		}
	}
	return;
}
