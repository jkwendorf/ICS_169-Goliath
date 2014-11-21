
#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::FloatRect
{
private:
	bool collidable, grappleable, interactable;
	Tile();
public:
	Tile(sf::Vector2f pos, sf::Vector2f dim, bool canCollide = true, bool grappleable = false, bool interactable = false);
	~Tile();
	bool getCollidable();
	bool getGrappleable();
	bool getInteractable();
};