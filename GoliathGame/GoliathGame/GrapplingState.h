#pragma once 

#include "BaseState.h"

class GrapplingState : public BaseState
{
public:
	GrapplingState();
	virtual void enter(Player* player);
	virtual void handleInput(Player* player, Command* input);
	virtual void update(Player* player, float deltaTime);
	virtual void exit();
};