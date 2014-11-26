#include "Enemy.h"
#include "PhysicsManager.h"

Enemy::Enemy() : BaseObject()
{

}

//Probably still need to work on some more overloads
Enemy::Enemy(sf::String body, float x, float y)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);

	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{

}

void Enemy::draw(sf::RenderWindow& window)
{
	BaseObject::draw(window);
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

void Enemy::enemyUpdate(CollisionManager* cM, float deltaTime, sf::Vector2i lSize)
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

	if(movingRight)
	{
		move(moveHorizontally(*this, RIGHT, false, deltaTime)); 
		if(cM->playerCollisionDetection(this))
		{
			move(moveOutOfTileHorizontally(*this, cM->getCollidedTile(*this)));
			movingRight = false;
		}
		else if ((sprite.getPosition().x + (PLAYER_DIM_X / 2)) > lSize.x)
		{
			sprite.setPosition((lSize.x - (PLAYER_DIM_X / 2)), sprite.getPosition().y);
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
		else if ((sprite.getPosition().x - (PLAYER_DIM_X / 2)) < 0)
		{
			sprite.setPosition((PLAYER_DIM_X / 2), sprite.getPosition().y);
			movingRight = true;
		}
	}
}