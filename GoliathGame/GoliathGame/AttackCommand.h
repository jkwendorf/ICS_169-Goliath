#pragma once

#include "Command.h"

class AttackCommand : public Command
{
private:
	Player* player;
public: 
	AttackCommand(Player* player_, Input inputCode_);
	virtual void execute();

};