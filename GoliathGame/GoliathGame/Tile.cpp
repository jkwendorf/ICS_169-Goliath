
#include "Tile.h"

Tile::Tile(sf::Vector2f& pos_, int tileNum_, uint8 flags_)
	:sf::FloatRect(pos_, sf::Vector2f(GAME_TILE_DIM, GAME_TILE_DIM)), tileNum(tileNum_), flags(flags_)
{

}

Tile::~Tile()
{

}

int Tile::getTileNum()
{
	return tileNum;
}

uint8 Tile::getFlags()
{
`   	return flags;
}

void Tile::changeOpened()
{
	flags += 0x10;
}