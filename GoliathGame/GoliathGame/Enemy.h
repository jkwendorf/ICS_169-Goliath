#pragma once

#include "BaseObject.h"

class Enemy : public BaseObject
{
public:
	Enemy();
	Enemy(sf::String body, float x, float y);
	~Enemy();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void move(float x, float y);
	void move(sf::Vector2f& distance);
	void destroy();

	float health;
	int weapon;
	float weaponCooldown;
};