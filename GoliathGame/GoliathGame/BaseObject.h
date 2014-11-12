#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

class BaseObject
{
public:
	// METHODS AND FUNCTIONS
	BaseObject();
	BaseObject(bool canCollide);
	~BaseObject();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	
	// VARIABLES
	sf::Sprite sprite;
	sf::Vector2f vel;
	bool isFalling;
	bool collidable;
};