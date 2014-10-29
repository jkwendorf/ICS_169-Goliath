#pragma once

#include "BaseObject.h"
#include "HookShot.h"
//#include "Sword.h"
//#include "CrossBow.h"

enum WeaponEnum
{
	SWORD,
	CROSSBOW,
	HOOKSHOT
};

class Player : public BaseObject
{
public:
	// METHODS AND FUNCTIONS
	Player();
	~Player();

	void update(float deltaTime);
	void attack();
	void move(float x, float y);
	void draw(sf::RenderWindow& window);

	// VARIABLES
	sf::Vector2f vel;
	float stamina;
	float health;
	int weapon;
	HookShot hShot;
};