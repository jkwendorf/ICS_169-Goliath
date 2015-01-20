#include "Enemy.h"
#include "PhysicsManager.h"



//Probably still need to work on some more overloads
Enemy::Enemy(sf::String body, float x, float y) : 
	health(100.0f)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);
	//For testing
	//attackRange = 30;
	//jumpSpeed = -400;
	//patrolRange = 100;
	//moveSpeed = 150;

	attackRange = Global::GetInstance().enemyAttributes[0];
	jumpSpeed = Global::GetInstance().enemyAttributes[1];
	patrolRange = Global::GetInstance().enemyAttributes[2];
	moveSpeed = Global::GetInstance().enemyAttributes[3];

	initialPosition = sf::Vector2f(x,y);
	raycast = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));

	weaponCooldown = 2.0f;
	currentCooldown = 2.0f;


	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
		ammo[x].damage = 20.0f;
	}
	eSword.damage = 20.0f;
}

Enemy::Enemy(sf::String body, float x, float y, float range) : 
	health(100.0f), attackRange(range)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);

	//For testing
	jumpSpeed = -400;
	patrolRange = 20;
	moveSpeed = 250;
	initialPosition = sf::Vector2f(x,y);

	weaponCooldown = 2.0f;
	currentCooldown = 2.0f;


	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
		ammo[x].damage = 20.0f;
	}
	eSword.damage = 20.0f;
}

//USE THIS CONSTRUCTOR AND NOTHING ELSE
Enemy::Enemy(sf::String body, float x, float y, float range, float jp, float ms, float tRange) :
	attackRange(range), health(100.0f), jumpSpeed(-1 * jp), moveSpeed(ms), patrolRange(tRange)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);

	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	initialPosition = sf::Vector2f(x,y);

	raycast = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));

	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
		ammo[x].damage = 20.0f;
	}
}

Enemy::~Enemy()
{
	//delete[] ammo;
}

void Enemy::update(float deltaTime)
{
	for(int x = 0; x < 3; x++)
	{
		if(!ammo[x].moving)
			ammo[x].setLocation(sprite.getPosition());
		ammo[x].update(deltaTime);
	}

	eSword.update(deltaTime);

	if(!raycast.moving)
	{
		if(isMovingRight())
		{
			raycast.velocity.x = 10.0f;
		}
		else
		{
			raycast.velocity.x = -10.0f;
		}
		raycast.moving = true;
	}

	raycast.update(deltaTime);
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
		eSword.draw(window);
		if(raycast.moving)
		{
			raycast.draw(window);
		}
	}
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

void Enemy::enemyUpdate(float deltaTime, sf::Vector2i roomSize)
{
	enemyCheck(roomSize);

	update(deltaTime);
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

		rangeAttack(deltaTime);

	}
	else if(attackRange <= ENEMY_ATTACK_LOW_THRESHOLD)
	{
		meleeAttack(deltaTime);
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

void Enemy::meleeAttack(float deltaTime)
{
	if(currentCooldown >= weaponCooldown)
	{
		if(movingRight)
		{
			eSword.hitBox.setPosition(sprite.getPosition().x + PLAYER_DIM_X*1.5, sprite.getPosition().y);
		}
		else
		{
			eSword.hitBox.setPosition(sprite.getPosition().x - PLAYER_DIM_X*1.5, sprite.getPosition().y);
		}
		eSword.attacking = true;
		currentCooldown = 0.0f;
	}
	else if(eSword.attacking)
	{
		eSword.attacking = false;
	}
	currentCooldown += deltaTime;
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

bool Enemy::isMovingRight()
{
	return movingRight;
}

void Enemy::changeMove()
{
	movingRight = !movingRight;
}