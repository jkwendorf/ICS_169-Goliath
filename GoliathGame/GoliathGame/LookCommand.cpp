#include "LookCommand.h"


LookCommand::LookCommand(Player* player_, float deltaTime_, LookDirection direction_, Input inputCode_)
	:player(player_), deltaTime(deltaTime_), dir(direction_)
{
	inputCode = inputCode_;
}

void LookCommand::execute()
{
	player->viewMove(deltaTime, dir);
}
