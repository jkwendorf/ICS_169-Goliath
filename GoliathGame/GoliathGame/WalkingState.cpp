#include "WalkingState.h"
#include "JumpingState.h"
#include "PhysicsManager.h"

WalkingState::WalkingState()
{}

void WalkingState::enter() 
{
}

void WalkingState::handleInput(Player* player, Command* input) 
{
	OnGroundState::handleInput(player, input);
}

void WalkingState::update(Player* player, float deltaTime) 
{
	OnGroundState::update(player, deltaTime);

	if(!player->collisionManager->tileBelowCharacter(player))
	{
		//std::cout << "Start Falling" << std::endl;
		player->isFalling = true;
		player->currentState = new JumpingState();
	}
	else if(player->collisionManager->tileBelowCharacter(player))
	{
		if(player->hShot.isDisabled)
			player->hShot.isDisabled = false;
		
		//std::cout << "Ground Collision" << std::endl;
		if(player->collisionManager->wallBlockingCharacter(player))
		{
			player->move(moveOutOfTileHorizontally(*player, player->collisionManager->getCollidedTile(*player)));
		}
	}
}

void WalkingState::exit() 
{
}