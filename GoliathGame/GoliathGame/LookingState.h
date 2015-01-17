#pragma once 

#include "OnGroundState.h"

class LookingState : public OnGroundState
{
public:
	LookingState();
	void enter();
	void handleInput(Player* player, Command* input);
	void update(Player* player, float deltaTime);
	void exit();
private:
	float viewChanged;
};