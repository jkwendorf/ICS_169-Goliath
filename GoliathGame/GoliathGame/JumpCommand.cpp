#include "JumpCommand.h"

JumpCommand::JumpCommand(Player* player_)
	:player(player_)
{
}

void JumpCommand::execute()
{
	player->jump();
}