#pragma once

#include "Command.h"

class GrappleCommand : public Command
{
private:
	Player* player;
public: 
	GrappleCommand(Player* player_, Input inputCode_);
	virtual void execute();

};