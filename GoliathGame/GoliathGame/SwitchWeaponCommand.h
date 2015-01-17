#pragma once

#include "Command.h"

class SwitchWeaponCommand : public Command
{
private:
	Player* player;
public: 
	SwitchWeaponCommand(Player* player_, Input inputCode_);
	virtual void execute();

};