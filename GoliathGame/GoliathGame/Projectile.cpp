#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f vel) :
	startLocation(startPos), velocity(vel), moving(false)
{
	bulletAnimation = Animation(10, 1, 64, 64, .10);
	//source = sf::Vector2i(0,0);
	//projectileTexture = TextureManager::GetInstance().retrieveTexture("haduken");
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("haduken2"));
	//sprite.scale(0.75,0.5);
	endTime = 2.0;
	startTime = 0.0;
	//sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	rectangle = sf::RectangleShape(sf::Vector2f(36,36));
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
				bulletAnimation.update(deltaTime, sprite, 0, false);
			else if(velocity.x > 0)
				bulletAnimation.update(deltaTime, sprite, 0, true);
			//sprite.move(velocity.x * 100 * deltaTime, velocity.y * 100 * deltaTime);
			sprite.move(velocity.x * 750 * deltaTime, velocity.y * 750 * deltaTime);
		}
		else
		{
			moving = false;
			startTime = 0.0;
		}
	}
	rectangle.setPosition(sprite.getPosition().x + 18, sprite.getPosition().y + 18);
}

void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	
	//rectangle.setFillColor(sf::Color::Red);
	//window.draw(rectangle);
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