#pragma once

#include "Command.h"

class MoveCommand : public Command
{
private:
	MovementDirection dir;
	float deltaTime;
	Player* player;
public: 
	MoveCommand();
	void init(Player* player_, MovementDirection direction_, float deltaTime_, Input inputCode_);
	virtual void execute();

};