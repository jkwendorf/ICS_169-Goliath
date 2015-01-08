#include "WalkingState.h"

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
}

void WalkingState::exit() 
{
}