#include "RunCommand.h"

RunCommand::RunCommand(Player* player_, Input inputCode_)
	:player(player_)
{
	inputCode = inputCode_;
}

void RunCommand::execute()
{
	player->running = true;
}