#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f vel) :
	startLocation(startPos), velocity(vel), moving(false)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("alkf"));
	sprite.scale(0.1,0.1);
	endTime = 2.0;
	startTime = 0.0;
}

Projectile::~Projectile()
{

}

void Projectile::update(float deltaTime)
{
	
	if(moving)
	{
		startTime += deltaTime;
		if(startTime < endTime)
			sprite.move(velocity.x * 100 * deltaTime, 0.0);
		else
		{
			moving = false;
			startTime = 0.0;
		}
	}
}

void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Projectile::setLocation(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Projectile::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}