#pragma once 

#include "OnGroundState.h"

class WalkingState : public OnGroundState
{
public:
	WalkingState();
	void enter();
	void handleInput(Player* player, Command* input);
	void update(Player* player, float deltaTime) ;
	void exit();
};