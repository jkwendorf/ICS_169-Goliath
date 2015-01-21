
#include "ClimbCommand.h"

ClimbCommand::ClimbCommand(Player* player_, Input inputCode_)
	:player(player_)
{
	inputCode = inputCode_;
}

void ClimbCommand::execute()
{
	player->interpolateVaultAboveGrappleTile();
}