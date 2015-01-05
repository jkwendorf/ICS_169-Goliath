#pragma once

#include "BaseState.h"

class OnGroundState : public BaseState
{
public:
	virtual void handleInput(Player& player, Input input)
	{
		if(input == RUN)
		{

		}
		else if (input == MOVELEFT)
		{

		}
		else if (input == MOVERIGHT)
		{

		}
		else if (input == ATTACK)
		{

		}
		else if (input == JUMP)
		{
			// Jump...
		}
		else if (input == GRAPPLE)
		{
			// Duck...
		}
	}
};