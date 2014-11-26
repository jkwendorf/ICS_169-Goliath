#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::hookCollisionDetection(HookShot hs)
{
	for(Tile* b : grapplableTileList)
	{
		//b->sprite.setColor(sf::Color::Red);
		if(b->intersects(hs.sprite.getGlobalBounds()) && b->getGrappleable())
			return true;
	}
	return false;
}

bool CollisionManager::playerCollisionDetection(BaseObject* p)
{
	for(Tile* b : tileList)
	{
		//std::cout << "(" << b->sprite.getGlobalBounds().left << "," << b->sprite.getGlobalBounds().top << ")";
		//std::cout << "(" << p.sprite.getGlobalBounds().left << "," << p.sprite.getGlobalBounds().top << ")" << std::endl;
		//b->sprite.setColor(sf::Color::Red);
		if(b->intersects(p->sprite.getGlobalBounds()))
			return true;
	}
	//std::cout << "\n\n\n\n";
	return false;
}


Tile* CollisionManager::getCollidedTile(BaseObject p)
{
	for(Tile* b : tileList)
		if(b->intersects(p.sprite.getGlobalBounds()))
			return b;
	return NULL;
}

void CollisionManager::setNearByTiles(std::vector<Tile*> tiles)
{
	tileList = tiles;
}

void CollisionManager::setGrapplableTiles(std::vector<Tile*> tiles)
{
	grapplableTileList = tiles;
}