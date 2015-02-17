#pragma once

#include <string> 
#include <vector>
#include "LayerStruct.h"

struct RoomStruct
{
	int roomSize;
	std::string nonMovinglayer;
	std::vector<LayerStruct> movingLayers;
};