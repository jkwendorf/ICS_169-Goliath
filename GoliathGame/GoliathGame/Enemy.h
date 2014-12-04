#pragma once

#include "BaseObject.h"
#include "Projectile.h"
//#include "CollisionManager.h"

class Enemy : public BaseObject
{
public:
	Enemy();
	Enemy(sf::String body, float x, float y);
	Enemy(sf::String body, float x, float y, float range);
	~Enemy();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void move(float x, float y);
	void move(sf::Vector2f& distance);
	void destroy();
	void enemyUpdate(float deltaTime, sf::Vector2i roomSize);
	float health;
	void attack(sf::Vector2f pPosition, float deltaTime);
	float attackRange;
	bool isMovingRight();
	void changeMove();

private:
	int weapon;
	float weaponCooldown;
	float currentCooldown;
	bool movingRight;
	bool isInScreen();
	void enemyCheck(sf::Vector2i roomSize);
	void rangeAttack(float deltaTime);
	void meleeAttack();
	bool attacked(); //To be more defined to run away from player if being attacked
	bool destroyed; //NEED TO FIGURE OUT ENEMY DESTRUCTION

	Projectile ammo[3];
};