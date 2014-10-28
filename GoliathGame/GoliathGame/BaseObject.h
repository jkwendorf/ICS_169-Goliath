#pragma once

#include <SFML/Graphics.hpp>

class BaseObject
{
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	sf::Sprite sprite;
};