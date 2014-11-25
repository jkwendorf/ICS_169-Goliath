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
	bool playerCollisionDetection(Player p);
	bool enemyCollision();
	
	void setNearByTiles(std::vector<Tile*> tiles);
	void setGrapplableTiles(std::vector<Tile*> tiles);
	bool hookCollisionDetection(HookShot hs);
	
	Tile* getCollidedTile(Player p);

private:
	std::vector<Tile*> tileList;
	std::vector<Tile*> grapplableTileList;
};