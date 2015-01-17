#pragma once

#include "Command.h"

class LookCommand : public Command
{
private:
	Player* player;
	float deltaTime;
	LookDirection dir;
public: 
	LookCommand(Player* player_, float deltaTime_, LookDirection direction_, Input inputCode_);
	virtual void execute();

};