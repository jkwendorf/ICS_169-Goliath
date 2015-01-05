#include "GrappleCommand.h"

GrappleCommand::GrappleCommand(Player* player_)
	:player(player_)
{
}

void GrappleCommand::execute()
{
	player->grapple();
}