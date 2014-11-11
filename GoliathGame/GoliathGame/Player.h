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
	void move(sf::Vector2f& dist);
	void grapple();
	void draw(sf::RenderWindow& window);

	// VARIABLES
	float stamina;
	float health;
	float weaponCooldown;
	float currentCooldown;
	int weapon;
	HookShot hShot;

	bool grappleInProgress, facingRight;
};