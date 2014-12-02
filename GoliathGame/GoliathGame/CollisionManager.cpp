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

bool CollisionManager::tileBelowCharacter(BaseObject* p)
{
	float left = p->sprite.getPosition().x - p->sprite.getGlobalBounds().width/2,
		right = p->sprite.getPosition().x + p->sprite.getGlobalBounds().width/2;

	for(Tile* b : tileList)
	{
		//if(b->intersects(p->sprite.getGlobalBounds()) && b->top >= p->sprite.getPosition().y)
		if(b->top >= p->sprite.getPosition().y)
			if((b->left <= left && b->left + b->width >= left) ||
				(b->left <= right && b->left + b->width >= right))
			return true;
	}
	return false;
}

bool CollisionManager::wallBlockingCharacter(BaseObject* p)
{
	for(Tile* b: tileList)
	{
		if(b->intersects(p->sprite.getGlobalBounds()))
		{
			if(b->top + b->height > p->sprite.getPosition().y - p->sprite.getGlobalBounds().height/2 + 0.1f)
				return true;
		}
	}
	return false;
}

int CollisionManager::numTilesNear(BaseObject p)
{
	return tileList.size();
}