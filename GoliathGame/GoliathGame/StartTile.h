#pragma once

#include "GroundTile.h"

class StartTile
{
private:
	StartTile();
	sf::RectangleShape collider;
	bool playerCollide(sf::RectangleShape playerRect);
public:
	StartTile(sf::Vector2i pos, sf::Vector2i screenOffSet);
	~StartTile();
	void update(float deltaTime);
};