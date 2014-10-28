#pragma once

#include "BaseObject.h"

class Player : public BaseObject
{
public:
	Player();
	~Player();

	void update(float deltaTime);
	void attack();
	void move();
	void draw(sf::RenderWindow& window);
};