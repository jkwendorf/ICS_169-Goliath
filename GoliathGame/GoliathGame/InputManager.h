#pragma once
#include <list>
#include <SFML\Graphics.hpp>
#include "Global.h"
#include "Player.h"
#include "CollisionManager.h"
#include "StaticCommandHolder.h"


class InputManager
{
public:
	InputManager();
	InputManager(int controllerScheme);

	~InputManager();

	//movement[0] = left
	//movement[1] = right
	bool movement[2];

	//utlity[0] = run
	//utility[1] = jump
	//utility[2] = grapple
	//utility[3] = attack
	//utility[4] = sword
	//utility[5] = lookup
	//utility[6] = lookdown
	bool utility[7];


	//controller[0] = game pad
	//controller[1] = keyboard/mouse
	//controller[2] = keyboard only
	bool controller[3];

	void update(Player& s, sf::View* v, float deltaTime);
	void playerMove(Player& s, float deltaTime);
	void viewMove(sf::View* v, Player& s, float deltaTime);

	float inputCooldown, currentInputCooldown;
	float weaponSwitchCooldown, currentWeaponSwitchCooldown;
	float viewDifference, viewChangedY, viewChangedX;
	float grappleCooldown, currentGrappleCooldown;
	bool grappleReset;
private:
	StaticCommandHolder sch;
};