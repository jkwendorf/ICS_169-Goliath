#pragma once

#include "Global.h"

class NonMovingLayer
{
public:
	NonMovingLayer(RoomStruct& roomStrct, int layerNumber);

	void Update();
	void draw(sf::RenderWindow& window);
	
	bool inFront;

private:
	sf::Sprite image;
};

