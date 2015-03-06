#pragma once

#include "Global.h"
#include "RoomStruct.h"
#include "Layer.h"
#include "NonMovingLayer.h"

class Background
{
private:
	sf::Sprite nonMovingLayer;
	std::vector<Layer> movingLayers;
	//std::vector<sf::Sprite> nonMovingLayers;
	//std::map<std::string, std::vector<sf::Sprite>> nonMovingLayers;
	std::vector<NonMovingLayer> nonMovingLayers;
	sf::Vector2f vel;
	sf::Clock clock;
	bool hitGround;
	float timerForStep, goliathStepWait, goliathMove, goliathStepTimer;

	Background();
public:
	Background(int levelNum, int roomNum);
	~Background();
	void setScale(int layerNum, float xScale, float yScale=1);
	void update(float deltaTime, float viewX);
	void draw(sf::RenderWindow& window);

	void setHitFloor(bool b);
	bool hitFloor();
	void reset();

};

