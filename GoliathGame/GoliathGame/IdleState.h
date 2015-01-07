#pragma once 

#include "OnGroundState.h"

class IdleState : public OnGroundState
{
public:
	IdleState();
	void enter();
	void handleInput(Player* player, Command* input);
	void update(Command* input, float deltaTime);
	void exit();
};