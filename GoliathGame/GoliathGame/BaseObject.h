#pragma once

#include <SFML/Graphics/Sprite.hpp>

class BaseObject
{
public:
	sf::Sprite sprite;
	void draw(sf::Texture* text, int x, int y);
};