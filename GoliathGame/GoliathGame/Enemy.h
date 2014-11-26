#pragma once

#include "BaseObject.h"
#include "CollisionManager.h"

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
	void enemyUpdate(CollisionManager* cM, float deltaTime, sf::Vector2i lSize);

private:
	float health;
	int weapon;
	float weaponCooldown;
	bool movingRight;
};