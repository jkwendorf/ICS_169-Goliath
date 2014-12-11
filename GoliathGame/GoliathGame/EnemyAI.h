#pragma once

#include <SFML\Graphics.hpp>
#include "Enemy.h"
#include "CollisionManager.h"

class EnemyAI
{
public:
	EnemyAI(CollisionManager* cm);
	~EnemyAI();

	void executeMovement(Enemy* e, sf::Vector2f pPosition, float deltaTime);
	void moveOutOfOtherEnemy(Enemy* e, Enemy* ne, float deltaTime);

private:
	CollisionManager* colMan;
	void moveToPlayer(Enemy* e, sf::Vector2f pPosition, float deltaTime);
	void normalMove(Enemy* e, float deltaTime);
	bool inRange(Enemy* e, sf::Vector2f pPosition);
	bool inAttackRange(Enemy* e, sf::Vector2f pPosition);
	void gravity(Enemy* e, float deltaTime);
	bool playerOnLeft(Enemy* e, sf::Vector2f pPosition);
	void moveOutOfPlayer(Enemy* e, sf::Vector2f pPosition, float deltaTime);
};