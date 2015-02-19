#pragma once

#include <deque>

#include "BaseObject.h"
#include "BaseState.h"
#include "HookShot.h"
#include "Projectile.h"
#include "UserInterface.h"
#include "Tile.h"
#include "Sword.h"
#include "CollisionManager.h"
#include "Command.h"
#include "Animation.h"

//#include "CrossBow.h"

#ifndef LOOK_DIR
#define LOOK_DIR

enum LookDirection
{
	UP = -1,
	DOWN = 1,

};

#endif // MOVE_DIR

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

enum SoundEnum
{
	ATTACKSOUND = 0,
	JUMPSOUND = 1,
	SHOOTSOUND = 2,
	TAKEDMGSOUND = 3,
	HOOKSOUND = 4
};

class BaseState;
class JumpingState;
class Command;
class CollisionManager;

class Player : public BaseObject, public Observer
{
public:
	// METHODS AND FUNCTIONS
	Player();
	~Player();
	void init(CollisionManager* collisionManager_, BaseState* startState);

	void handleInput();
	void update(float deltaTime);
	void takeDamage();
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
	void instantVaultAboveGrappleTile();
	void interpolateVaultAboveGrappleTile();

	void viewMove(float deltaTime, float& viewChanged_, LookDirection dir);
	void drawUI(sf::RenderWindow& window);

	void onNotify(const BaseObject& entity, Util::Events e);

	bool checkDead();
	void resetHealth();

	// VARIABLES
	float stamina;
	float health;
	float weaponCooldown;
	float currentCooldown;
	int weapon;
	int bottomPoint;
	HookShot hShot;
	sf::Vector2f grappleDir, vaultPos;

	bool grappleInProgress, facingRight, running, shouldHang, isHanging, isVaulting, collidingLeft, collidingRight;
	Projectile ammo[3];
	void viewCheck(sf::View* view, int width, int height);
	Sword playerSword;
	bool atTopEdge, atBottomEdge, atTheBottom;

	void updateUI();
	void updateUI(sf::Vector2f offset);

	sf::View* view;
	BaseState* currentState;
	BaseState* newState;
	CollisionManager* collisionManager;
	std::deque<Command*> inputQueue;
	sf::Sprite crosshair;
	Tile closestGrappleTile;
	Animation player;
	//sf::RectangleShape hitbox;
private:	
	sf::Sound soundEffects[5];
	float deathTimer;

	UserInterface* ui;
	void SetUpAugments();
	void SetUpEffects();
};