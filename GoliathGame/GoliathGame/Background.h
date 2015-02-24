#pragma once

#include "Global.h"
#include "RoomStruct.h"
#include "Layer.h"

class Background
{
private:
	sf::Sprite nonMovingLayer;
	std::vector<Layer> movingLayers;
	sf::Vector2f vel;
	sf::Clock clock;

	Background();
public:
	Background(int levelNum, int roomNum);
	~Background();
	void setScale(int layerNum, float xScale, float yScale=1);
	void update(float deltaTime, float viewX);
	void draw(sf::RenderWindow& window);

	void reset();

};

