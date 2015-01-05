#pragma once

#include "Player.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};