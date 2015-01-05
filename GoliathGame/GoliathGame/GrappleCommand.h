#pragma once

#include "Command.h"

class GrappleCommand : public Command
{
private:
	Player* player;
public: 
	GrappleCommand(Player* player_);
	virtual void execute();

};