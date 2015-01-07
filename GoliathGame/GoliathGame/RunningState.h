#pragma once 

#include "OnGroundState.h"

class RunningState : public OnGroundState
{
public:
	RunningState();
	void enter();
	void handleInput(Player* player, Command* input);
	void update(Command* input, float deltaTime);
	void exit();
};