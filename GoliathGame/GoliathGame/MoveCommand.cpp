#include "MoveCommand.h"

MoveCommand::MoveCommand(Player* player_, MovementDirection direction_, float deltaTime_)
	:player(player_), dir(direction_), deltaTime(deltaTime_)
{
}

void MoveCommand::execute()
{
	player->horizontalAcceleration(dir, deltaTime);
	if (dir==RIGHT)
		player->facingRight=true;
	else if (dir==LEFT)
		player->facingRight=false;
	player->verticalAcceleration(deltaTime);
	player->move(player->vel*deltaTime);
}