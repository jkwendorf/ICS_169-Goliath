#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

bool CollisionManager::hookCollisionDetection(HookShot hs)
{
	for(BaseObject b : tileList)
		if(b.sprite.getGlobalBounds().intersects(hs.sprite.getGlobalBounds()))
			return true;
	return false;
}

bool CollisionManager::playerCollisionDetection(Player p)
{
	for(BaseObject b : tileList)
		if(b.sprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds()))
			return true;
	return false;
}

BaseObject* CollisionManager::getCollidedTile(Player p)
{
	for(BaseObject b : tileList)
		if(b.sprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds()))
			return &b;
	return NULL;
}

void CollisionManager::setNearByTiles(std::vector<BaseObject> tiles)
{
	tileList = tiles;
}