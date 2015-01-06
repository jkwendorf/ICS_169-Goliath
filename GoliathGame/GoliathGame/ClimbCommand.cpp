
#include "ClimbCommand.h"

ClimbCommand::ClimbCommand(Player* player_)
	:player(player_)
{}

void ClimbCommand::execute()
{
	player->interpolateVaultAboveGrappleTile();
}