#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f vel) :
	startLocation(startPos), velocity(vel), moving(false)
{
	source = sf::Vector2i(0,0);
	//projectileTexture = TextureManager::GetInstance().retrieveTexture("haduken");
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("haduken"));
	//sprite.scale(0.75,0.5);
	endTime = 2.0;
	startTime = 0.0;
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

Projectile::~Projectile()
{

}

void Projectile::update(float deltaTime)
{
	//startTime += deltaTime;
	if(moving)
	{
		startTime += deltaTime;
		if(startTime < endTime)
		{
			if(velocity.x < 0)
				source.y = 1;
			else if(velocity.x > 0)
				source.y = 0;
			sprite.move(velocity.x * 100 * deltaTime, 0.0);
			sprite.setTextureRect(sf::IntRect(source.x * 64, source.y * 64, 64, 64));
			source.x++;
			if(source.x > 5)
				source.x = 0;
		}
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
	if(!moving)
		velocity = vel;
}