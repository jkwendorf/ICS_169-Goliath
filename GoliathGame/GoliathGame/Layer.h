#pragma once

#include "Global.h"

class Layer
{
private:
	Layer();
public:
	sf::Sprite image[2];
	sf::Vector2f scale;
	int layerNum;
	float degrees;
	float timeToRotate;
	float currentDegrees;
	bool rotateForward;

	Layer(RoomStruct& roomStrct, int layerNum);
	void update(float deltaTime, sf::Vector2f& vel);
	void draw(sf::RenderWindow& window);
	void reset();
};