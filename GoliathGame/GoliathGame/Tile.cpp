
#include "Tile.h"

Tile::Tile(sf::Vector2f pos, sf::Vector2f dim, int tileNum, bool canCollide, bool grappleable, bool interactable)
	:sf::FloatRect(pos, dim), tileNum(tileNum), collidable(canCollide), grappleable(grappleable), interactable(interactable)
{

}
Tile::~Tile()
{
	
}

int Tile::getTileNum()
{
	return tileNum;
}

bool Tile::getCollidable()
{
	return collidable;
}

bool Tile::getGrappleable()
{
	return grappleable;
}

bool Tile::getInteractable()
{
	return interactable;
}