#pragma once

#include <string> 
#include <vector>
#include "LayerStruct.h"

struct RoomStruct
{
	int roomSize;
	bool open;
	bool foundAll;
	std::string nonMovinglayer;
	std::vector<LayerStruct> movingLayers;
	sf::Vector2f posOffset;
};