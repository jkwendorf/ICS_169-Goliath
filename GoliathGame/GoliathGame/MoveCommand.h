#pragma once

#include "Command.h"

class MoveCommand : public Command
{
private:
	MovementDirection dir;
	float deltaTime;
	Player* player;
public: 
	MoveCommand(Player* player_, MovementDirection direction_, float deltaTime_);
	virtual void execute();

};