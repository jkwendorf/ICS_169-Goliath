
#include "Tile.h"

Tile::Tile(sf::Vector2f pos, sf::Vector2f dim, bool canCollide, bool grappleable, bool interactable)
	:sf::FloatRect(pos, dim), collidable(canCollide), grappleable(grappleable), interactable(interactable)
{

}
Tile::~Tile()
{
	
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