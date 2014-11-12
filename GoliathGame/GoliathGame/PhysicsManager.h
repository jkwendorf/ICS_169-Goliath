#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "BaseObject.h"

#define TERMINAL_VELOCITY 5
#define GRAVITY 0.5

// JW: moveDistance only worries about falling right now, will need to handle left and right motion in the future
//inline sf::Vector2f moveDistance(BaseObject& b, BaseObject* tiles, float deltaTime)
inline sf::Vector2f moveDistance(BaseObject& b, float deltaTime)
{
	if(b.isFalling)
	{
		if(b.vel.y >= TERMINAL_VELOCITY)
		{
			b.vel.y = TERMINAL_VELOCITY;
		}
		else
		{
			b.vel.y += 0.5*(pow(GRAVITY, 2));
		}

		/*if(b is colliding with something below them)
		{
			b.isFalling = false;
			b.vel.y = 0.f;

			return distance to bottom of tile
		}
		else if(b is colliding with something above them)
		{
			b.vel.y = 0.f;
			
			return distance to top of tile
		}
		else*/
		return sf::Vector2f(0.f, b.vel.y*deltaTime);
	}
	else
	{
		b.vel.y = 0.f;
		//if(b isn't colliding with something below them)
			//b.isFalling = true;

		return sf::Vector2f(0.f, 0.f);
	}
}

inline void jump(BaseObject& b)
{
	b.vel.y = -5.f;
	b.isFalling = true;
}