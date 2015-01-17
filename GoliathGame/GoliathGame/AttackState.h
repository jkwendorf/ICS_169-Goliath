#pragma once 

#include "BaseState.h"

class AttackState : public BaseState
{
public:
	AttackState();
	void enter(Player* player);
	virtual void handleInput(Player* player, Command* input);
	virtual void update(Player* player, float deltaTime);
	virtual void exit();
};