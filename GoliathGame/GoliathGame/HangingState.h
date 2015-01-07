#pragma once 

#include "BaseState.h"

class HangingState : public BaseState
{
public:
	HangingState();
	virtual void enter();
	virtual void handleInput(Player* player, Command* input);
	virtual void update(Command* input, float deltaTime);
	virtual void exit();
};