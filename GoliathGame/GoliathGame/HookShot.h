#pragma once
#include "Weapon.h"
 
class HookShot : public Weapon
{
public:
	sf::Vector2f grappleLocation;
	sf::Vector2f startLocation;
	int grappleLength;

	HookShot();
	~HookShot();
	void update(float deltaTime);
	void update(sf::Vector2f pos);
	void draw(sf::RenderWindow& window);
	void attack();
	void grappleToLocation(sf::Vector2f location);
	bool hookedOnSomething, grappleInProgress;

};