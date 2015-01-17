#include "IdleState.h"

IdleState::IdleState()
{
}

void IdleState::enter() 
{
	//Change to the idle animation 
}
void IdleState::handleInput(Player* player, Command* input) 
{
	if (input->inputCode == LOOKUP || input->inputCode == LOOKDOWN)
	{
		player->newState = new LookingState();
		input->execute();
	}
	else
	{
		OnGroundState::handleInput(player, input);
	}
	
}
void IdleState::update(Player* player, float deltaTime) 
{

}

void IdleState::exit() 
{

}