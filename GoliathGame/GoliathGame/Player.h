#pragma once
#include "BaseObject.h"
#include "HookShot.h"
#include "Projectile.h"
#include "UserInterface.h"
//#include "Sword.h"
//#include "CrossBow.h"

/*enum MovementDirection
{
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};*/

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
	void jump();
	//void accelerate(MovementDirection dir);
	void grapple();
	void resetPosition(sf::Vector2f& newPos);
	void draw(sf::RenderWindow& window);
	void playerUpdate(sf::View* view, sf::Vector2i roomSize, float deltaTime);

	// VARIABLES
	float stamina;
	float health;
	float weaponCooldown;
	float currentCooldown;
	int weapon;
	HookShot hShot;
	sf::Vector2f grappleDir;

	bool grappleInProgress, facingRight;
	Projectile ammo[3];

private:
	void viewCheck(sf::View* view, int width, int height);
	UserInterface* ui;
};