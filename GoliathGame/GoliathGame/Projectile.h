#pragma once
#include <SFML\Graphics.hpp>
#include "BaseObject.h"

class Projectile : public BaseObject
{
public:
	Projectile();
	~Projectile();

	sf::Vector2f startLocation;
	sf::Vector2f velocity;
	float endTime;

	void draw(sf::RenderWindow& window);
	void update(float deltaTime);

};