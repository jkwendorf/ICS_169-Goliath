#include "Enemy.h"
#include "PhysicsManager.h"

Enemy::Enemy() : BaseObject()
{

}

//Probably still need to work on some more overloads
Enemy::Enemy(sf::String body, float x, float y) :
	BaseObject()
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);

	//For testing
	attackRange = 500;

	weaponCooldown = 2.0f;
	currentCooldown = 2.0f;

	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
	}
}

Enemy::Enemy(sf::String body, float x, float y, float range) :
	BaseObject(), attackRange(range)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);

	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
	}
}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{
	for(int x = 0; x < 3; x++)
	{
		if(!ammo[x].moving)
			ammo[x].setLocation(sprite.getPosition());
		ammo[x].update(deltaTime);
	}
}

void Enemy::draw(sf::RenderWindow& window)
{
	//UNCOMMENT TO TEST ENEMY APPEARENCE
	if(isInScreen())
	{
		BaseObject::draw(window);
		for(int x = 0; x < 3; x++)
		{
			if(ammo[x].moving)
			{
				ammo[x].draw(window);
			}
		}
	//	std::cout << " is in screen" << std::endl;
	}
	//else std::cout << " not in screen" << std::endl;
}

void Enemy::move(float x, float y)
{
	sprite.move(x, y);
}

void Enemy::move(sf::Vector2f& distance)
{
	sprite.move(distance);
}

void Enemy::destroy()
{
	//allows the enemy to be taken off the screen
}

void Enemy::enemyUpdate(CollisionManager* cM, float deltaTime, sf::Vector2i roomSize, sf::Vector2f pPosition)
{
	gravity(cM, deltaTime);

	//if enemy isn't in range of player, handle normally
	if((movingRight && sprite.getPosition().x - pPosition.x > 0) || (!movingRight && sprite.getPosition().x - pPosition.x < 0))
	{
		if(inRange(pPosition))
		{
			moveToPlayer(cM, pPosition, deltaTime);
		}
		else normalMove(cM, deltaTime);
	}
	else
	{
		normalMove(cM, deltaTime);
	}

	if(inAttackRange(pPosition))
	{
		attack(pPosition, deltaTime);
	}

	enemyCheck(roomSize);

	update(deltaTime);
}

void Enemy::gravity(CollisionManager* cM, float deltaTime)
{
	move(moveVertically(*this, deltaTime));
	if(cM->playerCollisionDetection(this))
	{
		move(moveOutOfTileVertically(*this, cM->getCollidedTile(*this)));
	}
	else if(!isFalling)
	{
		isFalling = true;
	}
}

void Enemy::normalMove(CollisionManager* cM, float deltaTime)
{
	if(movingRight)
	{
		move(moveHorizontally(*this, RIGHT, false, deltaTime)); 
		if(cM->playerCollisionDetection(this))
		{
			move(moveOutOfTileHorizontally(*this, cM->getCollidedTile(*this)));
			movingRight = false;
		}

	}
	else
	{
		move(moveHorizontally(*this, LEFT, false, deltaTime));
		if(cM->playerCollisionDetection(this))
		{
			move(moveOutOfTileHorizontally(*this, cM->getCollidedTile(*this)));
			movingRight = true;
		}
	}
}

void Enemy::moveToPlayer(CollisionManager* cM, sf::Vector2f pPosition, float deltaTime)
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
	if(sprite.getPosition().x != pPosition.x)
	{
		if(playerOnLeft(pPosition))
		{
			movingRight = false;
			move(moveHorizontally(*this, LEFT, false, deltaTime)); 
		}
		else 
		{
			movingRight = true;
			move(moveHorizontally(*this, RIGHT, false, deltaTime)); 
		}
	}

	//if you come across a wall, jump
	if(cM->playerCollisionDetection(this))
	{
		move(moveOutOfTileHorizontally(*this, cM->getCollidedTile(*this)));
		vel.y = JUMP_SPEED;
		isFalling = true;
	}
	
}

bool Enemy::playerOnLeft(sf::Vector2f pPosition)
{
	if(sprite.getPosition().x > pPosition.x)
	{
		return true;
	}
	else return false;
}

bool Enemy::inRange(sf::Vector2f pPosition)
{
	if((sprite.getPosition().x + (GAME_TILE_DIM * 6)) > pPosition.x && (sprite.getPosition().x - (GAME_TILE_DIM * 6)) < pPosition.x)
	{
		return true;
	}
	else return false;
}

bool Enemy::inAttackRange(sf::Vector2f pPosition)
{
	if((sprite.getPosition().x + attackRange) > pPosition.x && (sprite.getPosition().x - attackRange) < pPosition.x)
	{
		if(sprite.getPosition().y == pPosition.y)
		{
			return true;
		}
	}
	else return false;
}

void Enemy::enemyCheck(sf::Vector2i roomSize)
{
	if ((sprite.getPosition().x - (PLAYER_DIM_X / 2)) < 0)
	{
		sprite.setPosition((PLAYER_DIM_X / 2), sprite.getPosition().y);
		movingRight = true;
	}
	else if ((sprite.getPosition().x + (PLAYER_DIM_X / 2)) > roomSize.x - 1)
	{
		sprite.setPosition((roomSize.x - 1 - (PLAYER_DIM_X / 2)), sprite.getPosition().y);
		movingRight = false;
	}
}

void Enemy::attack(sf::Vector2f pPosition, float deltaTime)
{
	if(attackRange >= ENEMY_ATTACK_HIGH_THRESHOLD)
	{
		if(playerOnLeft(pPosition) && !movingRight)
		{
			rangeAttack(deltaTime);
		}
		else if (!playerOnLeft(pPosition) && movingRight)
		{
			rangeAttack(deltaTime);
		}
	}
	else if(attackRange <= ENEMY_ATTACK_LOW_THRESHOLD)
	{
		if(playerOnLeft(pPosition) && !movingRight)
		{
			meleeAttack();
		}
		else if (!playerOnLeft(pPosition) && movingRight)
		{
			meleeAttack();
		}
	}

}

void Enemy::rangeAttack(float deltaTime)
{
	float xSpeed;
	if(currentCooldown >= weaponCooldown)
	{
		for(int x = 0; x < 3; x++)
		{
			if(!ammo[x].moving)
			{

				if(movingRight)
				{
					xSpeed = 10.0;
				}
				else
				{
					xSpeed = -10.0;
				}

				ammo[x].setVelocity(sf::Vector2f(xSpeed,0.0));
				ammo[x].moving = true;

				currentCooldown = 0.0f;
				break;
			}
		}
	}
	currentCooldown += deltaTime;
}

void Enemy::meleeAttack()
{

}

bool Enemy::isInScreen()
{
	if(sprite.getPosition().x > Global::GetInstance().topLeft.x - Global::GetInstance().xOffset &&
		sprite.getPosition().x < Global::GetInstance().topLeft.x + SCREEN_WIDTH +  Global::GetInstance().xOffset && 
		sprite.getPosition().y > Global::GetInstance().topLeft.y - Global::GetInstance().yOffset &&
		sprite.getPosition().y < Global::GetInstance().topLeft.y + SCREEN_HEIGHT + Global::GetInstance().yOffset)
	{
		return true;
	}
	else return false;
}