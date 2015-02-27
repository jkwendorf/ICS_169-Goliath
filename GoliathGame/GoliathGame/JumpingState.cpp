#include "JumpingState.h"

JumpingState::JumpingState()
{

}

void JumpingState::enter() 
{
}

void JumpingState::handleInput(Player* player, Command* input) 
{
	if((input->inputCode == MOVELEFT ||
		input->inputCode == MOVERIGHT ||
		input->inputCode == NO_MOVE) && !player->isHanging)
	{
		input->execute();
	}
	if(input->inputCode == GRAPPLE)
		input->execute();
}

void JumpingState::update(Player* player, float deltaTime) 
{
	if(!player->isFalling)
		player->isFalling = true;

	if(!player->isVaulting)
		player->verticalAcceleration(deltaTime);
	player->move(player->vel*deltaTime);
	
	if(player->collisionManager->playerCollisionDetection(player))
	{
		int currentCount = 0;

		while(player->collisionManager->playerCollisionDetection(player))
		{
			player->moveOutOfTile(player->collisionManager->getCollidedTile(*player), currentCount);
			currentCount++;
		}
	}
	else
	{
		player->collidingRight = false;
		player->collidingLeft = false;
	}
}

void JumpingState::exit() 
{
}