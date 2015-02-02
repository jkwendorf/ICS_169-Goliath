#pragma once
#include "BaseState.h"

class VaultingState : public BaseState
{
public:
	VaultingState(void);
	void enter();
	void handleInput(Player* player, Command* input);
	void update(Player* player, float deltaTime);
	void exit();
};
