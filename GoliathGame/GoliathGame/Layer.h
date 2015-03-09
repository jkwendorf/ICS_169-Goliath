#pragma once

#include "Global.h"

class Layer
{
private:
	Layer();
	float mViewX;
public:
	sf::Sprite image[2];
	sf::Vector2f scale;
	sf::Vector2f posOffset;
	int layerNum;
	float degrees;
	float timeToRotate;
	float currentDegrees;
	bool rotateForward;
	bool inFront;

	Layer(RoomStruct& roomStrct, int layerNum);
	void update(float deltaTime, sf::Vector2f& vel);
	void draw(sf::RenderWindow& window);
	void reset();

	void setViewX(float viewX);
};