#include "GrapplingState.h"

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
}

void GrapplingState::exit() 
{
}