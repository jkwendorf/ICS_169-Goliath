#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
	addObserver(Global::GetInstance().inventory);

}


CollisionManager::~CollisionManager()
{
}

bool CollisionManager::hookCollisionDetection(HookShot hs)
{
	for(Tile* b : grapplableTileList)
	{
		//b->sprite.setColor(sf::Color::Red);
		if(b->intersects(hs.sprite.getGlobalBounds()) && ((b->getFlags() & TILE::GRAPPLEABLEMASK) != 0))
			return true;
	}
	return false;
}

bool CollisionManager::playerCollisionDetection(BaseObject* p)
{
	for(Tile* b : tileList)
	{
		//std::cout << "(" << b.left << "," << b.top << ")";
		
		if(b->intersects(p->sprite.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

Tile CollisionManager::getNearestGrappleTile(BaseObject p)
{

	/* using flags
	->getFlags()
	& TILE::COLLIDABLEMASK) != 0
	will tell you if it is collidable

	*/
	Tile closestTile;
	if((grapplableTileList.front()->getFlags() & TILE::GRAPPLEABLEMASK) != 0)
		closestTile = *grapplableTileList.front();
	for(Tile* b: grapplableTileList)
		if(sqrt(pow(((b->top + b->height/2) - p.sprite.getPosition().y),2) + pow(((b->left + b->width/2)  - p.sprite.getPosition().x),2)) < 
			sqrt(pow(((closestTile.top + closestTile.height/2) - p.sprite.getPosition().y),2) + pow(((closestTile.left + closestTile.width/2) - p.sprite.getPosition().x),2)) )
		{
			if(((b->getFlags() & TILE::GRAPPLEABLEMASK) != 0))
				closestTile = *b;
		}

	return closestTile;
}
void CollisionManager::checkTreasure(BaseObject* p)
{
	for(Tile* b : tileList)
	{
		if(b->intersects(p->sprite.getGlobalBounds()))
		{
			if(((b->getFlags() & TILE::OPENEDMASK) == 0) && ((b->getFlags() & TILE::TREASUREMASK) != 0))
			{
 				notify(*p, Util::Events::PICK_UP_ITEM);
				b->changeOpened();
				return;
			}
		}
	}
}

Tile* CollisionManager::getCollidedTile(BaseObject p)
{
	for(Tile* b : tileList)
		if(b->intersects(p.sprite.getGlobalBounds()))
		{
			return b;
		}
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
		if(b->top >= p->sprite.getPosition().y + p->sprite.getGlobalBounds().height/2 && 
			b->top - (p->sprite.getPosition().y + p->sprite.getGlobalBounds().height/2) < GAME_TILE_DIM)
		{
			if((b->left <= left && b->left + b->width >= left) ||
				(b->left <= right && b->left + b->width >= right))
				return true;
		}
	}
	return false;
}

bool CollisionManager::wallBlockingCharacter(BaseObject* p)
{
	float top = ceil(p->sprite.getPosition().y - p->sprite.getGlobalBounds().height/2);
	for(Tile* b: tileList)
	{
		if(b->intersects(p->sprite.getGlobalBounds()))
		{
			if(b->top + b->height > top)
 				return true;
		}
	}
	return false;
}

int CollisionManager::numTilesNear(BaseObject p)
{
	return tileList.size();
}

Tile* CollisionManager::getHookedTile(HookShot hs)
{
	for(Tile* b : grapplableTileList)
	{
		if(b->intersects(hs.sprite.getGlobalBounds()) && ((b->getFlags() & TILE::GRAPPLEABLEMASK) != 0))
			return b;
	}
	return NULL;
}


void CollisionManager::checkPlayerBulletToEnemies(Projectile p, Enemy* enemy)
{
	//for(int x = 0; x < 3; x++)
	if(sqrt(pow(p.sprite.getPosition().x - enemy->sprite.getPosition().x, 2) + 
		pow(p.sprite.getPosition().y - enemy->sprite.getPosition().y, 2)) < 50 && p.moving)
	{
		enemy->health -= p.damage;
		p.moving = false;
	}
}

void CollisionManager::checkPlayerSwordToEnemies(Sword s, Enemy* enemy)
{
	if(sqrt(pow(s.hitBox.getPosition().x - enemy->sprite.getPosition().x, 2) + 
		pow(s.hitBox.getPosition().y - enemy->sprite.getPosition().y, 2)) < 75 && s.attacking)
		enemy->health -= s.damage;
}

void CollisionManager::checkEnemyBulletToPlayer(Projectile p, Player* player)
{
		if(sqrt(pow(p.sprite.getPosition().x - player->sprite.getPosition().x, 2) + 
			pow(p.sprite.getPosition().y - player->sprite.getPosition().y, 2)) < 50 && p.moving)
		{
			player->health -= p.damage;
			p.moving = false;
		}
}

void CollisionManager::checkEnemySwordToPlayer(Sword s, Player* player)
{
	if(sqrt(pow(s.hitBox.getPosition().x - player->sprite.getPosition().x, 2) + 
		pow(s.hitBox.getPosition().y - player->sprite.getPosition().y, 2)) < 75 && s.attacking)
	{
		if(s.attacking)
		{
			player->health -= s.damage;
		}
	}
}

bool CollisionManager::isGrappleListEmpty()
{
	for(Tile* tempTile : grapplableTileList)
		if(((tempTile->getFlags() & TILE::GRAPPLEABLEMASK) != 0))
			return false;
	return true;
}


bool CollisionManager::checkIfEnemyInRange(Projectile p, Player* player)
{
	if(sqrt(pow(p.sprite.getPosition().x - player->sprite.getPosition().x, 2) + 
		pow(p.sprite.getPosition().y - player->sprite.getPosition().y, 2)) < 50 && p.moving)
	{
		return true;
	}
	else return false;
}

bool CollisionManager::playerSwordCollideWithTile(Sword s, Tile* t)
{
	if(s.hitBox.getGlobalBounds().intersects(sf::FloatRect(t->left, t->top, t->width, t->height)))
		return true;

	return false;
}

bool CollisionManager::hShotHitNonGrappleTile(HookShot p)
{
	bool temp = false;
	for(Tile* tempTile : grapplableTileList)
	{
		
		if(tempTile->intersects(p.sprite.getGlobalBounds()) && 
			((tempTile->getFlags() & TILE::COLLIDABLEMASK) != 0) &&
			!((tempTile->getFlags() & TILE::GRAPPLEABLEMASK) != 0))
		{
			std::cout << "A tile Collision Occured" << std::endl;
			std::cout << "TempTile position" << std::endl;
			std::cout << tempTile->top << " " << tempTile->left << std::endl;
			return true;
		}
			
	}
	return temp;
}
