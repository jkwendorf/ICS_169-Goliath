
#include "Tile.h"

Tile::Tile(sf::Vector2f& pos_, int tileNum_, uint8 flags_)
	:sf::FloatRect(pos_, sf::Vector2f(GAME_TILE_DIM, GAME_TILE_DIM)), tileNum(tileNum_), flags(flags_), dir(sf::Vector2f(0,0)), health(1)
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
	return flags;
}

void Tile::changeOpened()
{
	flags += 0x10;
}

sf::Vector2f Tile::getDirection()
{
	return dir;
}

void Tile::setDirection(sf::Vector2f dir)
{
	this->dir = dir;
}

bool Tile::isWaitOver(float deltaTime)
{
	if(waitTime >= 0.f)
	{
		waitTime += deltaTime;

		if(waitTime >= 1.0f)
		{
			waitTime = -1.0f;
			return true;
		}
		return false;
	}

	return true;
}

void Tile::takeDamage()
{
	--health;
	waitTime = 0.f;
}

bool Tile::isHealthZero()
{
	if(health == 0)
		return true;
	return false;
}