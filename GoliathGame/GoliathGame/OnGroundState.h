#pragma once

#include "BaseState.h"


class OnGroundState : public BaseState
{
public:
	void handleInput(Player* player, Command* input);
};