#include "Player.h"
#include "Global.h"

Player::Player() 
	: BaseObject(), grappleInProgress(false), facingRight(true)
{
	vel = sf::Vector2f(0.0,0.0);
	
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("Test2"));
	//sprite.setPosition(64, 560);
	sprite.setPosition(150, 64);
	sprite.setScale( (PLAYER_DIM / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	weapon = CROSSBOW;
	weaponCooldown = 2.0f;
	currentCooldown = 0.0f;
	isFalling = true;
	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
	}
}

Player::~Player() 
{

}

void Player::update(float deltaTime)
{
	if(!hShot.grappleInProgress)
		if(facingRight)
			hShot.update(sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y - 15));
		else
			hShot.update(sf::Vector2f(sprite.getPosition().x - 60, sprite.getPosition().y - 15));
	else
	{
		hShot.update(deltaTime);
		if(sqrt(pow((std::abs(hShot.sprite.getPosition().x - sprite.getPosition().x)),2) + 
			pow((std::abs(hShot.sprite.getPosition().y - sprite.getPosition().y)),2)) >= 300)
		{
			hShot.grappleInProgress = false;
		}
	}

	for(int x = 0; x < 3; x++)
	{
		if(!ammo[x].moving)
			ammo[x].setLocation(sprite.getPosition());
		ammo[x].update(deltaTime);
	}
}

void Player::attack()
{
	if(weapon == CROSSBOW)
	{
		float xSpeed;
		for(int x = 0; x < 3; x++)
			if(!ammo[x].moving)
			{
				if(facingRight)
					xSpeed = 10.0;
				else
					xSpeed = -10.0;
				
				ammo[x].setVelocity(sf::Vector2f(xSpeed,0.0));
				ammo[x].moving = true;
				break;
			}
		/*
		if(ammo[0].velocity.x == 0)
			ammo[0].velocity.x ? facingRight =  10.0 : -10.0;
		else if(ammo[1].velocity.x == 0)
			ammo[1].velocity.x ? facingRight =  10.0 : -10.0;
		else if(ammo[2].velocity.x == 0)
			ammo[2].velocity.x ? facingRight =  10.0 : -10.0;
		*/
	}
}

void Player::move(float x, float y)
{
	sprite.move(x, y);
}

void Player::move(sf::Vector2f& distance)
{
	sprite.move(distance);
}

void Player::draw(sf::RenderWindow& window)
{
	BaseObject::draw(window);
	window.draw(hShot.sprite);
	//for(int x = 0; x < 3; x++)
	//	ammo[x].draw(window);
	/* //TESTING CIRCLE
	sf::CircleShape circle = sf::CircleShape(5.0);
	circle.setPosition(sprite.getPosition());
	circle.setFillColor(sf::Color::Red);
	window.draw(circle);
	*/

}

void Player::grapple()
{
	hShot.grappleInProgress = true;
	
	if(facingRight)
	{
		hShot.startLocation = sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y - 15);
		hShot.grappleToLocation(sf::Vector2f(sprite.getPosition().x + 300 , sprite.getPosition().y - 175));
	}
	else
	{
		hShot.startLocation = sf::Vector2f(sprite.getPosition().x - 60, sprite.getPosition().y - 15);
		hShot.grappleToLocation(sf::Vector2f(sprite.getPosition().x - 300 , sprite.getPosition().y - 175));
	}

}