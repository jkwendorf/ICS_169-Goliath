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
	else if(input->inputCode == GRAPPLE)
		input->execute();
}

void JumpingState::update(Player* player, float deltaTime) 
{
	if(!player->isFalling)
		player->isFalling = true;

	if(!player->isVaulting)
		player->verticalAcceleration(deltaTime);
	player->move(player->vel*deltaTime);

	while(player->collisionManager->playerCollisionDetection(player))
	{
		if((player->collisionManager->getCollidedTile(*player) != nullptr) && 
			((player->collisionManager->getCollidedTile(*player)->getFlags() & TILE::HAZARDMASK) != 0))
		{
			player->takeDamage();
		}
		player->moveOutOfTile(player->collisionManager->getCollidedTile(*player));
	}
}

void JumpingState::exit() 
{
}