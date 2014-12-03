#pragma once
#include <SFML\Graphics.hpp>
#include "TextureManager.h"
#include "BaseObject.h"

class Weapon : public BaseObject
{
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void attack() = 0;
	int damage;
	float weaponCooldown;
	float currentCooldown;
};