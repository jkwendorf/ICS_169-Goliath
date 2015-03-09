#pragma once

#include "Global.h"

class NonMovingLayer
{
public:
	NonMovingLayer(RoomStruct& roomStrct, int layerNumber);

	void Update(float deltaTime, sf::Vector2f vel);
	void draw(sf::RenderWindow& window);
	
	bool inFront;

private:
	sf::Vector2f scale;
	sf::Sprite image;
	float timeToRotate;
	float degreesToRotate;
	float currentDegrees;
	float currentTime;
};

