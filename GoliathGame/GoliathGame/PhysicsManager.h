#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "CollisionManager.h"

#define TERMINAL_VELOCITY 1000
#define JUMP_SPEED -450
#define GRAVITY 500
#define SPEED 100
#define BOOST 4

enum MovementDirection
{
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};

inline sf::Vector2f moveVertically(BaseObject& b, float deltaTime)
{
	sf::Vector2f dis;
	dis.x = 0.f;

	if(b.isFalling)
	{
		if(b.vel.y >= TERMINAL_VELOCITY)
			b.vel.y = TERMINAL_VELOCITY;
		else
			b.vel.y += GRAVITY * deltaTime;

		dis.y = b.vel.y*deltaTime;
	}
	else
		dis.y = 0.f;

	return dis;
}

inline sf::Vector2f moveHorizontally(BaseObject& b, MovementDirection dir, bool sprint, float deltaTime)
{
	sf::Vector2f dis;

	if(sprint)
		dis.x = dir*SPEED*BOOST*deltaTime;
	else
		dis.x = dir*SPEED*deltaTime;

	dis.y = 0.f;

	return dis;
}

inline sf::Vector2f moveOutOfTileVertically(BaseObject& p, BaseObject* t)
{
	sf::Vector2f newPos;

	// If colliding from above
	if(t->sprite.getPosition().y > p.sprite.getPosition().y)
	{
		p.isFalling = false;
		p.vel.y = 0.f;
		newPos.y = t->sprite.getPosition().y - p.sprite.getPosition().y - p.sprite.getGlobalBounds().height/2.f;
	}
	// If colliding from below
	else if(t->sprite.getPosition().y < p.sprite.getPosition().y)
	{			
		p.vel.y = 0.f;
		newPos.y = (t->sprite.getPosition().y + t->sprite.getGlobalBounds().height) - 
			(p.sprite.getPosition().y - p.sprite.getGlobalBounds().height/2.f);
	}

	//return sf::Vector2f(0.f, 0.f);
	return newPos;
}

inline sf::Vector2f moveOutOfTileHorizontally(BaseObject& p, BaseObject* t)
{
	sf::Vector2f newPos;
	// If the player is colliding with the left side of the tile
	if(p.sprite.getPosition().x < t->sprite.getPosition().x)
		newPos.x = t->sprite.getPosition().x - (p.sprite.getPosition().x + p.sprite.getGlobalBounds().width/2);
	// If the player is colliding with the right side of the tile
	else if(p.sprite.getPosition().x > t->sprite.getPosition().x + t->sprite.getGlobalBounds().width)
		newPos.x = (t->sprite.getPosition().x + t->sprite.getGlobalBounds().width) - (p.sprite.getPosition().x - p.sprite.getGlobalBounds().width/2);

	//return sf::Vector2f(0.f, 0.f);

	return newPos;
}

inline void jump(BaseObject& b)
{
	b.vel.y = JUMP_SPEED;
	b.isFalling = true;
}