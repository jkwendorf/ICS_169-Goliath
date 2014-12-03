#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "CollisionManager.h"
#include "Tile.h"
#include "Player.h"
#include "HookShot.h"
#include "Utility.h"

#define TERMINAL_VELOCITY 1000
#define JUMP_SPEED -450
#define GRAVITY 500
#define SPEED 100
#define MOVE_ACCEL 400
#define BOOST 4
#define GRAPPLE_SPEED 550

#ifndef MOVE_DIR
#define MOVE_DIR

enum MovementDirection
{
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};

#endif // MOVE_DIR

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

inline sf::Vector2f moveOutOfTileVertically(BaseObject& p, Tile* t)
{
	sf::Vector2f newPos;

	// If colliding from above
	if(t->top > p.sprite.getPosition().y)
	{
		p.isFalling = false;
		p.vel.y = 0.f;
		newPos.y = t->top - p.sprite.getPosition().y - p.sprite.getGlobalBounds().height/2.f -0.1f;
	}
	// If colliding from below
	else if(t->top < p.sprite.getPosition().y)
	{			
		p.vel.y = 0.f;
		newPos.y = (t->top + t->height) - 
			(p.sprite.getPosition().y - p.sprite.getGlobalBounds().height/2.f);
	}

	//return sf::Vector2f(0.f, 0.f);
	return newPos;
}

inline sf::Vector2f moveOutOfTileHorizontally(BaseObject& p, Tile* t)
{
 	sf::Vector2f newPos;
	// If the player is colliding with the left side of the tile
	if(p.sprite.getPosition().x < t->left)
		newPos.x = t->left - (p.sprite.getPosition().x + p.sprite.getGlobalBounds().width/2);
	// If the player is colliding with the right side of the tile
	else if(p.sprite.getPosition().x > t->left + t->width)
		newPos.x = (t->left + t->width) - (p.sprite.getPosition().x - p.sprite.getGlobalBounds().width/2);

	p.vel.x = 0;
	//return sf::Vector2f(0.f, 0.f);

	return newPos;
}

inline void grappleHookMove(Player& p, float& deltaTime)
{
	sf::Vector2f moveAmount(p.grappleDir*(deltaTime*GRAPPLE_SPEED));

	float length, maxDistance = distance(p.hShot.grappleLocation, p.sprite.getPosition());
	norm(moveAmount, length);

	//std::cout << moveAmount.x << " , " << moveAmount.y << " to " << maxDistance <<  std::endl;

	if(min(length, maxDistance) != length)
		moveAmount = p.hShot.grappleLocation - p.sprite.getPosition();

	p.move(moveAmount);
}