#pragma once

#include "Player.h"

enum Input
{
	MOVELEFT,
	MOVERIGHT,
	RUN,
	JUMP,
	GRAPPLE,
	ATTACK,
	LOOKUP,
	LOOKDOWN
};

class BaseState
{
public:
  virtual ~BaseState() {}
  virtual void handleInput(Player& heroine, Input input) {}
  virtual void update(Player& heroine) {}
};