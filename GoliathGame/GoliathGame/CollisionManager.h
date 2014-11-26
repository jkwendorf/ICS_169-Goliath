#pragma once
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "Player.h"
#include "Tile.h"


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	bool playerCollisionDetection(BaseObject* p);
	
	void setNearByTiles(std::vector<Tile*> tiles);
	void setGrapplableTiles(std::vector<Tile*> tiles);
	bool hookCollisionDetection(HookShot hs);
	
	Tile* getCollidedTile(BaseObject p);

private:
	std::vector<Tile*> tileList;
	std::vector<Tile*> grapplableTileList;
};