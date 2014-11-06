#pragma once

#include "GroundTile.h"

class Start
{
private:
	Start();
	sf::RectangleShape collider;
	bool playerCollide(sf::RectangleShape playerRect);
public:
	Start(sf::Vector2i pos, sf::Vector2i screenOffSet);
	~Start();
	void update(float deltaTime);
};