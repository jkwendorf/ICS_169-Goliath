
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

	};
}

class Tile : public sf::FloatRect
{
private:
	int tileNum;
	bool collidable, grappleable, interactable, treasure;
	uint8 flags;
	
public:
	Tile() : tileNum(-999), flags(0x00), collidable(false), grappleable(false), interactable(false),  treasure(false) {};
	Tile(sf::Vector2f& pos_, int tileNum_, uint8 flags_, bool canCollide_ = true, bool grappleable_ = false, bool interactable_ = false, bool treasure_ = false);
	~Tile();
	int getTileNum();
	bool getCollidable();
	bool getGrappleable();
	bool getInteractable();
	bool getTreasure();
	uint8 getFlags();
	void changeOpened();
};