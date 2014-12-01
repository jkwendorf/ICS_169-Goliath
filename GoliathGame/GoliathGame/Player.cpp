#include "Player.h"
#include "Global.h"
#include "PhysicsManager.h"

Player::Player() 
	: BaseObject(), grappleInProgress(false), facingRight(true)
{
	vel = sf::Vector2f(0.0,0.0);
	
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("David"));
	//sprite.setPosition(64, 560);
	sprite.setPosition(150, 64);
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
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
	grappleDir.y = 100;
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

		// If we're hooked onto something, grapple to point
		if(hShot.hookedOnSomething)
		{
			// If the direction isn't set, set it
			direction(hShot.grappleLocation, sprite.getPosition(), grappleDir);
			// Move to the point and do stuff
			grappleHookMove(*this, deltaTime);

			// If were at the point, end grappling and reset the direction
			if(distance(hShot.grappleLocation, sprite.getPosition()) < 5.f)
			{
				hShot.hookedOnSomething = false;
				hShot.grappleInProgress = false;
				isFalling = true;
				grappleDir.y = 100;
			}
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
				//break;
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

void Player::resetPosition(sf::Vector2f& newPos)
{
	sprite.setPosition(newPos);
}

void Player::jump()
{
	vel.y = JUMP_SPEED;
	isFalling = true;
}

void Player::playerUpdate(sf::View* view, sf::Vector2i roomSize, float deltaTime)
{
	viewCheck(view, roomSize.x, roomSize.y);
	update(deltaTime);
}

void Player::viewCheck(sf::View* view, int width, int height)
{
	if(facingRight)
	{
		if(sprite.getPosition().x > SCREEN_WIDTH - Global::GetInstance().xOffset + Global::GetInstance().topLeft.x)
		{
			Global::GetInstance().topLeft.x = sprite.getPosition().x - SCREEN_WIDTH + Global::GetInstance().xOffset;
		}
	}
	else
	{
		if(sprite.getPosition().x < Global::GetInstance().topLeft.x + Global::GetInstance().xOffset)
		{
			Global::GetInstance().topLeft.x = sprite.getPosition().x - Global::GetInstance().xOffset;
		}
	}

	if(Global::GetInstance().topLeft.x < 0)
	{
		Global::GetInstance().topLeft.x = 0;
	}

	if(width - Global::GetInstance().xOffset < sprite.getPosition().x)
	{
		Global::GetInstance().topLeft.x = width - SCREEN_WIDTH;
		if(width % SCREEN_WIDTH > 0)
		{
			Global::GetInstance().topLeft.x = (width / SCREEN_WIDTH) * SCREEN_WIDTH
				- SCREEN_WIDTH + (width % SCREEN_WIDTH);
		}
	}

	if(sprite.getPosition().y - (PLAYER_DIM_Y / 2) < 0 + Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = sprite.getPosition().y - (PLAYER_DIM_Y / 2) - Global::GetInstance().yOffset;
	}
	else if(sprite.getPosition().y + (PLAYER_DIM_Y / 2) > SCREEN_HEIGHT - Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = sprite.getPosition().y + (PLAYER_DIM_Y / 2) + Global::GetInstance().yOffset - SCREEN_HEIGHT;
	}

	if(Global::GetInstance().topLeft.y > height - SCREEN_HEIGHT)
	{
		Global::GetInstance().topLeft.y = height - SCREEN_HEIGHT;
	}
		
	if(Global::GetInstance().topLeft.x == 0)
	{
		if((sprite.getPosition().x - (PLAYER_DIM_X / 2)) < 0)
		{
			sprite.setPosition((0 + PLAYER_DIM_X /2), sprite.getPosition().y);
		}
	}
	else if(Global::GetInstance().topLeft.x == (width - SCREEN_WIDTH))
	{
		if((sprite.getPosition().x + (PLAYER_DIM_X / 2)) > (width - 1))
		{
			sprite.setPosition((width - 1 - (PLAYER_DIM_X / 2)), sprite.getPosition().y);
		}
	}

	view->reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}
/*void Player::accelerate(MovementDirection dir)
{
	if(dir != STILL)
	{
		float maxSpeed = SPEED;
		vel.x = MOVE_ACCEL*dir;
		vel.x = min(vel.x, maxSpeed);
	}
	else
	{

	}
}*/