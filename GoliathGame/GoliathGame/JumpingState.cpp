#include "JumpingState.h"

JumpingState::JumpingState()
{

}

void JumpingState::enter() 
{
}

void JumpingState::handleInput(Player* player, Command* input) 
{

}

void JumpingState::update(Command* input, float deltaTime) 
{
	input->execute();
}

void JumpingState::exit() 
{
}