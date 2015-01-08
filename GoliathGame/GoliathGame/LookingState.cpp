#include "LookingState.h"

LookingState::LookingState()
{
}

void LookingState::enter() 
{
	//Change to the idle animation 
}
void LookingState::handleInput(Player* player, Command* input) 
{
	OnGroundState::handleInput(player, input);
}
void LookingState::update(Player* player, float deltaTime) 
{

}

void LookingState::exit() 
{
	Global::GetInstance().topLeft.y -= viewChanged;
	viewChanged = 0;
}