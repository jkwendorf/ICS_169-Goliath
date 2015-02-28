#pragma once
#include "Weapon.h"


 
class HookShot : public Weapon
{
public:
	sf::Vector2f grappleLocation;
	sf::Vector2f startLocation;
	int grappleLength;
	int grappleBox;
	int hookshotSpeed;

	HookShot();
	~HookShot();
	void update(float deltaTime);
	void update(sf::Vector2f pos);
	void updateChain(sf::Vector2f playerPos);
	void draw(sf::RenderWindow& window);
	void attack();
	void grappleToLocation(sf::Vector2f location);
	bool hookedOnSomething, grappleInProgress, fireRight, isDisabled, hitNonGrappleTile;

	sf::Sprite hookshotChain[10];
};