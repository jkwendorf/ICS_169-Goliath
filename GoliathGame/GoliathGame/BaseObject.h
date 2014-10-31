#pragma once

#include <SFML/Graphics.hpp>

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Sprite sprite;
};