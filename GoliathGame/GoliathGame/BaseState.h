#pragma once

#include "Player.h"
#include "Command.h"

class Player;
class Command;

class BaseState
{
public:
	virtual ~BaseState() {}
	virtual void enter() {}
	virtual void handleInput(Player* player, Command* input) {};
	virtual void update(Player* player, float deltaTime) {}
	virtual void exit() {}

};