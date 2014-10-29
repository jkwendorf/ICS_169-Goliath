#pragma once
#include "Weapon.h"
 
class HookShot : public Weapon
{
public:
	sf::Vector2f vel;
	sf::Vector2f grappleLocation;

	HookShot();
	~HookShot();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void attack();
	void grappleToLocation(sf::Vector2f location);
};