#include <queue>
#include "Server.h"

using namespace server;

Server::Server()
{
	playerService = std::make_shared<PlayerService>();
	commandService = std::make_shared<CommandService>();
}
