#pragma once
#include "BaseObject.h"
#include "HookShot.h"
#include "Projectile.h"
#include "Tile.h"
//#include "Sword.h"
//#include "CrossBow.h"

#ifndef MOVE_DIR
#define MOVE_DIR

enum MovementDirection
{
	LEFT = -1,
	RIGHT = 1,
	STILL = 0
};

#endif // MOVE_DIR

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
	
	void playerMove(float& deltaTime);
	void horizontalAcceleration(MovementDirection dir, float& deltaTime);
	void verticalAcceleration(float& deltaTime);
	void moveOutOfTile(Tile* t);

	// VARIABLES
	float stamina;
	float health;
	float weaponCooldown;
	float currentCooldown;
	int weapon;
	HookShot hShot;
	sf::Vector2f grappleDir;

	bool grappleInProgress, facingRight, running;
	Projectile ammo[3];
	void viewCheck(sf::View* view, int width, int height);

private:
	
};