
#include "Tile.h"

Tile::Tile(sf::Vector2f& pos_, int tileNum_, uint8 flags_, bool canCollide_, bool grappleable_, bool interactable_, bool treasure_)
	:sf::FloatRect(pos_, sf::Vector2f(GAME_TILE_DIM, GAME_TILE_DIM)), tileNum(tileNum_), flags(flags_), collidable(canCollide_), 
	grappleable(grappleable_), interactable(interactable_), treasure(treasure_)
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

bool Tile::getTreasure()
{
	return treasure;
}

uint8 Tile::getFlags()
{
	return flags;
}

void Tile::changeOpened()
{
	flags += 0x10;
}