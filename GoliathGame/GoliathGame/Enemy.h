#pragma once

#include "BaseObject.h"
#include "Projectile.h"
#include "Sword.h"
//#include "CollisionManager.h"

class Enemy : public BaseObject
{
public:
	Enemy();
	Enemy(sf::String body, float x, float y);
	Enemy(sf::String body, float x, float y, float range);
	~Enemy();

	float health;
	float attackRange;

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void move(float x, float y);
	void move(sf::Vector2f& distance);
	void destroy();
	void enemyUpdate(float deltaTime, sf::Vector2i roomSize);
	void attack(sf::Vector2f pPosition, float deltaTime);
	bool isMovingRight();
	void changeMove();

	Projectile ammo[3];
	Sword eSword;

private:
	int weapon;
	float weaponCooldown;
	float currentCooldown;
	bool movingRight;
	bool isInScreen();
	void enemyCheck(sf::Vector2i roomSize);
	void rangeAttack(float deltaTime);
	void meleeAttack(float deltaTime);
	bool attacked(); //To be more defined to run away from player if being attacked
	bool destroyed; //NEED TO FIGURE OUT ENEMY DESTRUCTION


};