#pragma once

#include "GroundTile.h"

class EndTile
{
private:
	sf::RectangleShape collider;
	bool playerCollide(sf::RectangleShape playerRect);
public:
	void update(float deltaTime);
};