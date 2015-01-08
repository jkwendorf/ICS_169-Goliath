#pragma once 

#include "OnGroundState.h"
#include "LookingState.h"

class IdleState : public OnGroundState
{
public:
	IdleState();
	void enter();
	void handleInput(Player* player, Command* input);
	void update(Player* player, float deltaTime);
	void exit();
};