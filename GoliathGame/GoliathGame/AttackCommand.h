#pragma once

#include "Command.h"

class AttackCommand : public Command
{
private:
	Player* player;
public: 
	AttackCommand(Player* player_);
	virtual void execute();

};