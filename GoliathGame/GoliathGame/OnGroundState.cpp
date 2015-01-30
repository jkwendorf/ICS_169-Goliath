#include "OnGroundState.h"

#include "WalkingState.h"
#include "JumpingState.h"
#include "AttackState.h"
#include "GrapplingState.h"

void OnGroundState::handleInput(Player* player, Command* input)
{
	if (input->inputCode == MOVELEFT || input->inputCode == MOVERIGHT || input->inputCode == NO_MOVE)
	{
		player->newState = new WalkingState();
		input->execute();
	}
	else if (input->inputCode == ATTACK)
	{
		player->newState = new AttackState();
		input->execute();
	}
	else if (input->inputCode == JUMP)
	{
		player->newState = new JumpingState();
		input->execute();
	}
	else if (input->inputCode == GRAPPLE)
	{
		//player->newState = new GrapplingState();
		input->execute();
	}
	else
	{
		player->newState = NULL;
	}
	
}

void OnGroundState::update(Player* player, float deltaTime) 
{
	if(!player->hShot.grappleInProgress)
	{
		if(player->facingRight)
			player->hShot.update(sf::Vector2f(player->sprite.getPosition().x + 60, player->sprite.getPosition().y - 15));
		else
			player->hShot.update(sf::Vector2f(player->sprite.getPosition().x - 60, player->sprite.getPosition().y - 15));
	}
	player->move(player->vel*deltaTime);
}