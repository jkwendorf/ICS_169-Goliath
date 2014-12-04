#pragma once
#include "Weapon.h"

class Sword : public Weapon
{
public:
	Sword();
	~Sword();

	void draw(sf::RenderWindow &window);
	void update(float deltaTime);
	void attack();
	sf::RectangleShape hitBox;
	bool attacking;
};