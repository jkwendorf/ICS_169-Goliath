#pragma once

#include "Command.h"

class JumpCommand : public Command
{
private:
	Player* player;
public: 
	JumpCommand(Player* player_);
	virtual void execute();

};