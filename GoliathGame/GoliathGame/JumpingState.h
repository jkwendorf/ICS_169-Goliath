#pragma once 

#include "BaseState.h"


class JumpingState : public BaseState
{
public:
	JumpingState();
	void enter();
	void handleInput(Player* player, Command* input);
	void update(Player* player, float deltaTime);
	void exit();
};