#include "Projectile.h"

Projectile::Projectile()
{

}

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f vel, float rotation) :
	startLocation(startPos), velocity(vel), moving(false), drawPlease(true)
{
	//bulletAnimation = Animation(10, 1, 64, 64, .10);
	//bulletAnimation = Animation(2, 1, 250, 64, .10, false);
	//source = sf::Vector2i(0,0);
	//projectileTexture = TextureManager::GetInstance().retrieveTexture("haduken");
	//sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("haduken2"));
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("Arrow1"));
	sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
	if (rotation == 90.0f || rotation == 270.0f)
	{
		hitbox = sf::RectangleShape(sf::Vector2f(10,64));
	}
	else
	{
		hitbox = sf::RectangleShape(sf::Vector2f(64,10));
	}
	
	/*
	if (vel.y == 0) {
		hitbox = sf::RectangleShape(sf::Vector2f(64,10));
		sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("Arrow"));
		sprite.setScale(0.3f, 0.3f);
	}
	else {
		hitbox = sf::RectangleShape(sf::Vector2f(10,64));
		sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("ArrowVertical"));
		sprite.setScale(0.3f, 0.3f);
	}
	*/
	//sprite.scale(0.75,0.5);
	sprite.setScale(0.3f, 0.3f);
	
	endTime = 2.0;
	startTime = 0.0;
	//sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
	sprite.setTextureRect(sf::IntRect(0, 0, 250, 64));
	sprite.setPosition(startLocation.x, startLocation.y);

	//sf::Vector2f pos;
	
	sprite.rotate(rotation);
	//sprite.setOrigin(0, 0);
	//sprite.setPosition(pos);
	hitbox.setOrigin(hitbox.getGlobalBounds().width/2,hitbox.getGlobalBounds().height/2);
	hitbox.setPosition(sprite.getPosition());
	hitbox.setFillColor(sf::Color::Blue);
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
			//if(velocity.x < 0)
			//	bulletAnimation.update(deltaTime, sprite, 0, false);
			//else if(velocity.x > 0)
			//	bulletAnimation.update(deltaTime, sprite, 0, true);
			//sprite.move(velocity.x * 100 * deltaTime, velocity.y * 100 * deltaTime);
			sprite.move(velocity.x * 1500 * deltaTime, velocity.y * 1500 * deltaTime);
			drawPlease = true;
		}
		else
		{
			moving = false;
			startTime = 0.0;
		}
	}
	//rectangle.setPosition(sprite.getPosition().x + 18, sprite.getPosition().y + 18);
	BaseObject::update(deltaTime);
}

void Projectile::draw(sf::RenderWindow& window)
{
	if(drawPlease)
		BaseObject::draw(window);
	
	//hitbox.setFillColor(sf::Color::Red);
	//window.draw(hitbox);
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