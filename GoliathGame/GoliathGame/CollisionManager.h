#pragma once
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "Player.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	bool playerCollisionDetection(Player p);
	bool enemyCollision();
	void setNearByTiles(std::vector<BaseObject> tiles);
	BaseObject* getCollidedTile(Player p);

private:
	std::vector<BaseObject> tileList;
};