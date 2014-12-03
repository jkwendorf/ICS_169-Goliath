#include "Player.h"
#include "Global.h"
#include "PhysicsManager.h"

Player::Player() 
	: BaseObject(), grappleInProgress(false), facingRight(true),running(false),  health(100), stamina(50), ui(new UserInterface(health, stamina))
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
	{
		if(facingRight)
			hShot.update(sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y - 15));
		else
			hShot.update(sf::Vector2f(sprite.getPosition().x - 60, sprite.getPosition().y - 15));
	}
	else
	{
		hShot.update(deltaTime);
		if(sqrt(pow((std::abs(hShot.sprite.getPosition().x - sprite.getPosition().x)),2) + 
			pow((std::abs(hShot.sprite.getPosition().y - sprite.getPosition().y)),2)) >= 300)
		{
			hShot.grappleInProgress = false;
			hShot.hookedOnSomething = false;
		}
	}


	if(!hShot.hookedOnSomething || !hShot.grappleInProgress)
	{	
	// Move the player
		verticalAcceleration(deltaTime);


		if(running)
			move(vel*deltaTime);
		else
			move(vel*deltaTime);
	}
	else if(hShot.grappleInProgress && hShot.hookedOnSomething)
	{
		vel.x = 0.f;
		vel.y = 0.f;
		// If the direction isn't set, set it
		direction(hShot.grappleLocation, sprite.getPosition(), grappleDir);
		// Move to the point and do stuff
		grappleHookMove(*this, deltaTime);

		// If were at the point, end grappling and reset the direction
		if(hShot.grappleLocation == sprite.getPosition())
		{
			hShot.hookedOnSomething = false;
			hShot.grappleInProgress = false;
			isFalling = true;
			grappleDir.y = 100;
		}
	}	

	for(int x = 0; x < 3; x++)
	{
		if(!ammo[x].moving)
			ammo[x].setLocation(sprite.getPosition());
		ammo[x].update(deltaTime);
	}

	ui->update(health, stamina);
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
	ui->draw(window);
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
	if(!hShot.grappleInProgress)
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
			vel.x = 0.f;
		}
		else if((sprite.getPosition().x + (PLAYER_DIM_X / 2)) > (width - 1))
		{
			sprite.setPosition((width - 1 - (PLAYER_DIM_X / 2)), sprite.getPosition().y);
			vel.x = 0.f;
		}
	}
	else if(Global::GetInstance().topLeft.x == (width - SCREEN_WIDTH))
	{
		if((sprite.getPosition().x + (PLAYER_DIM_X / 2)) > (width - 1))
		{

      		sprite.setPosition((width - 1 - (PLAYER_DIM_X / 2)), sprite.getPosition().y);
			vel.x = 0.f;
		}
	}

	view->reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}


void Player::horizontalAcceleration(MovementDirection dir, float& deltaTime)
{

	if(!hShot.hookedOnSomething || !hShot.grappleInProgress)
	{
		if(dir != STILL)
		{
			float maxSpeed = SPEED;
			if(dir == LEFT)
			{ 
				maxSpeed = -1.f*maxSpeed;
				if(running)
				{
					maxSpeed *= BOOST;
					vel.x += MOVE_ACCEL*BOOST*dir*deltaTime;
				}
				else
					vel.x += MOVE_ACCEL*dir*deltaTime;

				vel.x = max(vel.x, maxSpeed);
			}
			else
			{
				if(running)
				{
					maxSpeed *= BOOST;
					vel.x += MOVE_ACCEL*BOOST*dir*deltaTime;
				}
				else
					vel.x += MOVE_ACCEL*dir*deltaTime;

				vel.x = min(vel.x, maxSpeed);
			}
		}
		else
		{
			if(vel.x > 0.f)
			{
				vel.x -= MOVE_ACCEL*deltaTime;
				if(vel.x <= 0.f)
					vel.x = 0.f;
			}
			else if(vel.x < 0.f)
			{
				vel.x += MOVE_ACCEL*deltaTime;
				if(vel.x >= 0.f)
					vel.x = 0.f;
			}
		}
	}
}

void Player::verticalAcceleration(float& deltaTime)
{
	if(isFalling)
	{
		if(vel.y >= TERMINAL_VELOCITY)
			vel.y = TERMINAL_VELOCITY;
		else
			vel.y += GRAVITY * deltaTime;
	}
}

void Player::moveOutOfTile(Tile* t)
{
	float left = (sprite.getPosition().x + sprite.getGlobalBounds().width/2) - t->left, 
		right = (t->left + t->width) - (sprite.getPosition().x - sprite.getGlobalBounds().width/2), 
		up = (sprite.getPosition().y + sprite.getGlobalBounds().height/2) - t->top, 
		down = (t->top + t->height) - (sprite.getPosition().y - sprite.getGlobalBounds().height/2);

	// Calculate shortest distance
	if(sgn(vel.x) > 0)
	{
		if(sgn(vel.y) > 0)
		{
			if(up >= left)
				move(moveOutOfTileHorizontally(*this, t));
			else
				move(moveOutOfTileVertically(*this, t));
		}
		else if(sgn(vel.y) < 0)
		{
			if(down >= left)
				move(moveOutOfTileHorizontally(*this, t));
			else
				move(moveOutOfTileVertically(*this, t));
		}
		else
		{
			move(moveOutOfTileHorizontally(*this, t));
		}
	}
	else if(sgn(vel.x) < 0)
	{
		if(sgn(vel.y) > 0)
		{
			if(up >= right)
				move(moveOutOfTileHorizontally(*this, t));
			else
				move(moveOutOfTileVertically(*this, t));
		}
		else if(sgn(vel.y) < 0)
		{
			if(down >= right)
				move(moveOutOfTileHorizontally(*this, t));
			else
				move(moveOutOfTileVertically(*this, t));
		}
		else
		{
			move(moveOutOfTileHorizontally(*this, t));
		}
	}
	else
	{
		move(moveOutOfTileVertically(*this, t));
	}

	// Move in direction of shortest distance
}
