#pragma once

#include <SFML/Graphics.hpp>

class BaseObject
{
public:
	BaseObject();
	BaseObject(bool canCollide);
	~BaseObject();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Sprite sprite;
	bool collidable;
};