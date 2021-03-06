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
	//moveOutOfPlayer(e, pPosition, deltaTime);
	gravity(e, deltaTime);

	if(e->foundPlayer)
	{
		std::cout << "Moving to Player" << std::endl;
		moveToPlayer(e, pPosition, deltaTime);
	}
	else normalMove(e, deltaTime);
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
	float movement;
	if(e->isMovingRight())
	{
		movement = e->moveSpeed * deltaTime;
		e->move(movement, 0);

		if(colMan->playerCollisionDetection(e))
		{
			e->move(moveOutOfTileHorizontally(*e, colMan->getCollidedTile(*e)));
			//e->changeMove();

			e->vel.y = e->jumpSpeed;
			e->isFalling = true;
		}
		else if(e->sprite.getPosition().x > e->initialPosition.x + (e->patrolRange / 2))
		{
			e->changeMove();
		}
	}
	else
	{
		movement = -1 * e->moveSpeed * deltaTime;
		e->move(movement, 0);
		//e->move(moveHorizontally(*e, LEFT, false, deltaTime / e->moveSpeed));
		if(colMan->playerCollisionDetection(e))
		{
			e->move(moveOutOfTileHorizontally(*e, colMan->getCollidedTile(*e)));
			//e->changeMove();

			e->vel.y = e->jumpSpeed;
			e->isFalling = true;
		}
		else if (e->sprite.getPosition().x < e->initialPosition.x - e->patrolRange / 2)
		{
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

	float movement;
	if(e->sprite.getPosition().x != pPosition.x)
	{
		if(playerOnLeft(e, pPosition))
		{
			if(e->isMovingRight())
			{
				e->changeMove();
			}
			movement = e->moveSpeed * deltaTime * -1;
			e->move(movement, 0);
		}
		else 
		{
			if(!e->isMovingRight())
			{
				e->changeMove();
			}
			movement = e->moveSpeed * deltaTime * 1;
			e->move(movement, 0);
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

void EnemyAI::moveOutOfOtherEnemy(Enemy* e, Enemy* ne, float deltaTime)
{
	if(playerOnLeft(e, ne->sprite.getPosition()))
	{
		e->sprite.setPosition(ne->sprite.getPosition().x + PLAYER_DIM_X, e->sprite.getPosition().y);
		if(e->isMovingRight() != ne->isMovingRight())
		{
			e->changeMove();
			e->move(moveHorizontally(*e, RIGHT, false, deltaTime)); 
		}
	}
	else
	{
		e->sprite.setPosition(ne->sprite.getPosition().x - PLAYER_DIM_X, e->sprite.getPosition().y);
		if(e->isMovingRight() != ne->isMovingRight())
		{
			e->changeMove();
			e->move(moveHorizontally(*e, LEFT, false, deltaTime)); 
		}
	}

	if(colMan->playerCollisionDetection(e))
	{
		e->move(moveOutOfTileHorizontally(*e, colMan->getCollidedTile(*e)));
		e->vel.y = JUMP_SPEED;
		e->isFalling = true;
	}
}

void EnemyAI::moveOutOfPlayer(Enemy* e, sf::Vector2f pPosition, float deltaTime)
{
	if(playerOnLeft(e, pPosition))
	{
		e->sprite.setPosition(pPosition.x + PLAYER_DIM_X, e->sprite.getPosition().y);
		e->changeMove();
		e->move(moveHorizontally(*e, RIGHT, false, deltaTime)); 
	}
	else
	{
		e->sprite.setPosition(pPosition.x - PLAYER_DIM_X, e->sprite.getPosition().y);
		e->changeMove();
		e->move(moveHorizontally(*e, LEFT, false, deltaTime)); 
	}

	if(colMan->playerCollisionDetection(e))
	{
		e->move(moveOutOfTileHorizontally(*e, colMan->getCollidedTile(*e)));
		e->vel.y = JUMP_SPEED;
		e->isFalling = true;
	}
}