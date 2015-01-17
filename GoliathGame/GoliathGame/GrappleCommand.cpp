#include "GrappleCommand.h"

GrappleCommand::GrappleCommand(Player* player_, Input inputCode_)
	:player(player_)
{
	inputCode = inputCode_;
}

void GrappleCommand::execute()
{
	player->grapple();
}