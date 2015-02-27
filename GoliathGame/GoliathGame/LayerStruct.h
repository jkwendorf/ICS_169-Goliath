#pragma once

#include <string>

struct LayerStruct
{
	std::string imageName;
	sf::Vector2f scale;
	sf::Vector2f posOffset;
	float degrees;
	float timeToRotate;
};