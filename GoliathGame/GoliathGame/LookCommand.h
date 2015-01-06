#pragma once

#include "Command.h"

class LookCommand : public Command
{
private:
	Player* player;
	sf::View* view;
	float deltaTime;
	LookDirection dir;
public: 
	LookCommand(Player* player_, sf::View* view_, float deltaTime_, LookDirection direction_);
	virtual void execute();

};