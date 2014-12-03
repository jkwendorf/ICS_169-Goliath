#include "EnemyAI.h"
#include "PhysicsManager.h"

EnemyAI::EnemyAI(CollisionManager* cM) : colMan(cM)
{

}

EnemyAI::~EnemyAI()
{

}

void EnemyAI::executeMovement(Enemy* e, sf::Vector2f pPosition, float deltaTime)
{
	gravity(e, deltaTime);

	//if enemy isn't in range of player, handle normally
	if((e->isMovingRight() && e->sprite.getPosition().x - pPosition.x > 0) 
		|| (!e->isMovingRight() && e->sprite.getPosition().x - pPosition.x < 0))
	{
		if(inRange(e, pPosition))
		{
			moveToPlayer(e, pPosition, deltaTime);
		}
		else normalMove(e, deltaTime);
	}
	else
	{
		normalMove(e, deltaTime);
	}
}

void EnemyAI::gravity(Enemy* e, float deltaTime)
{
	e->move(moveVertically(*e, deltaTime));
	if(colMan->playerCollisionDetection(e))
	{
		e->move(moveOutOfTileVertically(*e, colMan->getCollidedTile(*e)));
		e->isFalling = false;
	}
	else if(!e->isFalling)
	{
		e->isFalling = true;
	}
}

void EnemyAI::normalMove(Enemy* e, float deltaTime)
{
	if(e->isMovingRight())
	{
		e->move(moveHorizontally(*e, RIGHT, false, deltaTime)); 
		if(colMan->playerCollisionDetection(e))
		{
			e->move(moveOutOfTileHorizontally(*e, colMan->getCollidedTile(*e)));
			e->changeMove();
		}

	}
	else
	{
		e->move(moveHorizontally(*e, LEFT, false, deltaTime));
		if(colMan->playerCollisionDetection(e))
		{
			e->move(moveOutOfTileHorizontally(*e, colMan->getCollidedTile(*e)));
			e->changeMove();
		}
	}
}

void EnemyAI::moveToPlayer(Enemy* e, sf::Vector2f pPosition, float deltaTime)
{
	//move towards player


	//A* Search
	//	Heuristic is distance
	//	Restrictions are tiles
	//	Figure out how to convert screen Position to distance
	//	Figure out how to check screen position in terms of tiles
	//	Store bunch of coordinates
	//	if Player position is not that
	//		keep moving
	//		once you reach that next destination
	//		keep on going
	if(e->sprite.getPosition().x != pPosition.x)
	{
		if(playerOnLeft(e, pPosition))
		{
			e->changeMove();
			e->move(moveHorizontally(*e, LEFT, false, deltaTime)); 
		}
		else 
		{
			e->changeMove();
			e->move(moveHorizontally(*e, RIGHT, false, deltaTime)); 
		}
	}

	//if you come across a wall, jump
	if(colMan->playerCollisionDetection(e))
	{
		e->move(moveOutOfTileHorizontally(*e, colMan->getCollidedTile(*e)));
		e->vel.y = JUMP_SPEED;
		e->isFalling = true;
	}
	
	if(inAttackRange(e, pPosition))
	{
		e->attack(pPosition, deltaTime);
	}

}

bool EnemyAI::playerOnLeft(Enemy* e,sf::Vector2f pPosition)
{
	if(e->sprite.getPosition().x > pPosition.x)
	{
		return true;
	}
	else return false;
}

bool EnemyAI::inRange(Enemy* e, sf::Vector2f pPosition)
{
	if((e->sprite.getPosition().x + (GAME_TILE_DIM * 6)) > pPosition.x 
		&& (e->sprite.getPosition().x - (GAME_TILE_DIM * 6)) < pPosition.x)
	{
		return true;
	}
	else return false;
}

bool EnemyAI::inAttackRange(Enemy* e, sf::Vector2f pPosition)
{
	if((e->sprite.getPosition().x + e->attackRange) > pPosition.x 
		&& (e->sprite.getPosition().x - e->attackRange) < pPosition.x)
	{
		if(e->sprite.getPosition().y == pPosition.y)
		{
			return true;
		}
		else return false;
	}
	else return false;
}