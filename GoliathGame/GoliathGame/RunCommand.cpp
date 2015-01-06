#include "RunCommand.h"

RunCommand::RunCommand(Player* player_)
	:player(player_)
{
}

void RunCommand::execute()
{
	player->running = true;
}