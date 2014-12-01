
#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::FloatRect
{
private:
	int tileNum;
	bool collidable, grappleable, interactable;
	Tile();
public:
	Tile(sf::Vector2f pos, sf::Vector2f dim, int tileNum, bool canCollide = true, bool grappleable = false, bool interactable = false);
	~Tile();
	int getTileNum();
	bool getCollidable();
	bool getGrappleable();
	bool getInteractable();
};