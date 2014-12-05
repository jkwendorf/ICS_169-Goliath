#include "Enemy.h"
#include "PhysicsManager.h"



//Probably still need to work on some more overloads
Enemy::Enemy(sf::String body, float x, float y) : 
	health(100.0f)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);

	//For testing
	attackRange = 500;

	weaponCooldown = 2.0f;
	currentCooldown = 2.0f;

	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
	}
}

Enemy::Enemy(sf::String body, float x, float y, float range) :
	attackRange(range), health(100.0f)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture(body));
	sprite.setPosition(x, y);

	//ND: Change Player dimensions to whatever floats your boat
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
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
	//	std::cout << " is in screen" << std::endl;
	}
	//else std::cout << " not in screen" << std::endl;
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
		meleeAttack();
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

void Enemy::meleeAttack()
{

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