#include "GrapplingState.h"
//#include "Utility.h"
#include "PhysicsManager.h"
#include "HangingState.h"

GrapplingState::GrapplingState()
{}

void GrapplingState::enter(Player* player) 
{
}

void GrapplingState::handleInput(Player* player, Command* input) 
{
	if(input->inputCode == JUMP)
	{
		
	}
	else
	{
		
	}
}

void GrapplingState::update(Player* player, float deltaTime) 
{
	player->vel.x = 0.f;
	player->vel.y = 0.f;
	// If the direction isn't set, set it
	direction(player->hShot.grappleLocation, player->sprite.getPosition(), player->grappleDir);
	// Move to the point and do stuff
	grappleHookMove(*player, deltaTime);

	// If were at the point, end grappling and reset the direction
	if(player->hShot.grappleLocation == player->sprite.getPosition())
	{
		player->hShot.hookedOnSomething = false;
		player->hShot.grappleInProgress = false;
		player->isFalling = true;
		player->grappleDir.y = 100;
			
		if(player->shouldHang)
		{
			player->shouldHang = false;
			player->isHanging = true;
			
			// JW: Will need to think of a way of altering this so it's a command
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Joystick::isButtonPressed(0, 1))
			{
				player->interpolateVaultAboveGrappleTile();
			}
			else
				player->newState = new HangingState();
		}
	}
}

void GrapplingState::exit() 
{
}