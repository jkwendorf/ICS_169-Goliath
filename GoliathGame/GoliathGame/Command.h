#pragma once

#include "Player.h"

enum Input
{
	NONE,
	MOVELEFT,
	MOVERIGHT,
	RUN,
	JUMP,
	GRAPPLE,
	ATTACK,
	LOOKUP,
	LOOKDOWN
};

class Command
{
public:
	Input inputCode;
	virtual ~Command() {}
	virtual void execute() = 0;
};