#include "HangingState.h"
#include "JumpingState.h"

HangingState::HangingState()
{

}
void HangingState::enter() 
{

}

void HangingState::handleInput(Player* player, Command* input) 
{
	if(input->inputCode == CLIMB)
	{
		input->execute();
		//delete player->currentState;
		//player->currentState = new JumpingState();
		player->isFalling = true;
	}
}

void HangingState::update(Player* player, float deltaTime) 
{

}

void HangingState::exit() 
{
}