#include "MoveCommand.h"

MoveCommand::MoveCommand()
{
}

void MoveCommand::init(Player* player_, MovementDirection direction_, float deltaTime_, Input inputCode_)
{
	player = player_;
	dir = direction_; 
	deltaTime = deltaTime_;
	inputCode = inputCode_;
}
void MoveCommand::execute()
{
	player->horizontalAcceleration(dir, deltaTime);
	if (dir==RIGHT)
		player->facingRight=true;
	else if (dir==LEFT)
		player->facingRight=false;
	//player->verticalAcceleration(deltaTime);	
}