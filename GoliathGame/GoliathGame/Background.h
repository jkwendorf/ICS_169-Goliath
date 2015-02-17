#pragma once

#include "Global.h"
#include "RoomStruct.h"

struct Layer
{
	sf::Sprite image;
	float scale;
	int layerNum;
};

class Background
{
private:
	sf::Sprite nonMovingLayer;
	std::vector<Layer> movingLayers;
	sf::Vector2f vel;

	Background();
public:
	Background(int levelNum, int roomNum);
	~Background();
	void setScale(int layerNum, float xScale, float yScale=1);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void reset();

};

