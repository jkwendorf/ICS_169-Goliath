
#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"

namespace TILE
{
	enum 
	{
		COLLIDABLEMASK = 0x01,
		GRAPPLEABLEMASK = 0x02,
		INTERACTABLEMASK = 0x04,
		TREASUREMASK = 0x08,
		OPENEDMASK = 0x10,
		HAZARDMASK = 0X20,
		DESTRUCTABLEMASK = 0x30
	};
}

class Tile : public sf::FloatRect
{
private:
	int tileNum;
	bool collidable, grappleable, interactable, treasure;
	sf::Vector2f dir;
	uint8 flags;
	
public:
	Tile() : tileNum(-999), flags(0x00) {};
	Tile(sf::Vector2f& pos_, int tileNum_, uint8 flags_);
	~Tile();
	int getTileNum();
	uint8 getFlags();
	sf::Vector2f getDirection();
	void setDirection(sf::Vector2f dir);
	void changeOpened();
};