#pragma once

#include <string>

struct LayerStruct
{
	std::string imageName;
	sf::Vector2f scale;
	sf::Vector2f posOffset;
	sf::Vector2f sizeScale;
	float degrees;
	float timeToRotate;
	bool drawInFront;
};