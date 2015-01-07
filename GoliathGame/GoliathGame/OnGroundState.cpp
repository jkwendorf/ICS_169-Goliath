#include "OnGroundState.h"
#include "WalkingState.h"

void OnGroundState::handleInput(Player* player, Command* input)
{
	if (input->inputCode == MOVELEFT || input->inputCode == MOVERIGHT)
	{
		delete player->state;
		player->state = new WalkingState();
	}
	else if (input->inputCode == ATTACK)
	{
		delete player->state;
		player->state = new WalkingState();
	}
	else if (input->inputCode == JUMP)
	{
		delete player->state;
		player->state = new WalkingState();
	}
	else if (input->inputCode == GRAPPLE)
	{
		delete player->state;
		player->state = new WalkingState();
	}

}