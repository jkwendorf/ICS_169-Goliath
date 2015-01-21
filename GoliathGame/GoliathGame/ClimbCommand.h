#pragma once

#include "Command.h"

class ClimbCommand : public Command
{
private:
	Player* player;
public: 
	ClimbCommand(Player* player_, Input inputCode_);
	virtual void execute();

};