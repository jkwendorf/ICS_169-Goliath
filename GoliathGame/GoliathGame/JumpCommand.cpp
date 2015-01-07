#include "JumpCommand.h"

JumpCommand::JumpCommand(Player* player_, Input inputCode_)
	:player(player_)
{
	inputCode = inputCode_;
}

void JumpCommand::execute()
{
	player->jump();
}