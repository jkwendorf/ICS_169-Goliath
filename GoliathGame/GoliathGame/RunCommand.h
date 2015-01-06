#pragma once

#include "Command.h"

class RunCommand : public Command
{
private:
	Player* player;
public: 
	RunCommand(Player* player_);
	virtual void execute();

};