#include "Enemy.h"

Enemy::Enemy() : BaseObject()
{

}

//Probably still need to work on some more overloads
Enemy::Enemy(sf::String body, float x, float y)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);

	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime)
{
	if(sprite.getPosition().x > 1000 || sprite.getPosition().x < 100)
		movingRight = !movingRight;

	//More complex movement once the physics manager is good to go
	//Use this method to detect if the player is near by or is in vision.

	if(movingRight)
		move(100*deltaTime, 0*deltaTime);
	else
		move(-100*deltaTime, 0*deltaTime);
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