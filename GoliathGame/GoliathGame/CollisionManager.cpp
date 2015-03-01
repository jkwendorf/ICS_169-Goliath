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
		
		if(b->intersects(p->hitbox.getGlobalBounds()))
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
	float closest = sqrt(pow(((closestTile.top + closestTile.height/2) - p.sprite.getPosition().y),2) + pow(((closestTile.left + closestTile.width/2) - p.sprite.getPosition().x),2));
	for(Tile* b: grapplableTileList)
		if(sqrt(pow(((b->top + b->height/2) - p.sprite.getPosition().y),2) + pow(((b->left + b->width/2)  - p.sprite.getPosition().x),2)) < closest )
		{
			if(((b->getFlags() & TILE::GRAPPLEABLEMASK) != 0))
			{
				closestTile = *b;
				closest = sqrt(pow(((closestTile.top + closestTile.height/2) - p.sprite.getPosition().y),2) + pow(((closestTile.left + closestTile.width/2) - p.sprite.getPosition().x),2));
			}
		}

	return closestTile;
}
void CollisionManager::checkTreasure(Player& p)
{
	for(Tile* b : tileList)
	{
		if(b->intersects(p.sprite.getGlobalBounds()))
		{
			if(((b->getFlags() & TILE::OPENEDMASK) == 0) && ((b->getFlags() & TILE::TREASUREMASK) != 0))
			{
 				notify(p, Util::Events::PICK_UP_ITEM);
				p.ui->addTreasure();
				if(p.health < 100.0f)
				{
					p.health += 25.0f;
				}
				b->changeOpened();
				return;
			}
		}
	}
}

Tile* CollisionManager::getCollidedTile(BaseObject p)
{
	for(Tile* b : tileList)
		if(b->intersects(p.hitbox.getGlobalBounds()))
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
	float left = p->hitbox.getPosition().x - p->hitbox.getGlobalBounds().width/2,
		right = p->hitbox.getPosition().x + p->hitbox.getGlobalBounds().width/2;

	for(Tile* b : tileList)
	{
		if(b->top >= p->hitbox.getPosition().y + p->hitbox.getGlobalBounds().height/2 && 
			b->top - (p->hitbox.getPosition().y + p->hitbox.getGlobalBounds().height/2) < GAME_TILE_DIM)
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
	float top = ceil(p->hitbox.getPosition().y - p->hitbox.getGlobalBounds().height/2);
	for(Tile* b: tileList)
	{
		if(b->intersects(p->hitbox.getGlobalBounds()))
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
	if(p.hitbox.getGlobalBounds().intersects(enemy->hitbox.getGlobalBounds())&& p.moving)
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
	if(p.hitbox.getGlobalBounds().intersects(player->hitbox.getGlobalBounds()) && p.moving)
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
	if(p.hitbox.getGlobalBounds().intersects(player->hitbox.getGlobalBounds()) && p.moving)
	{
		/*std::cout << p.rectangle.getPosition().x << " " << p.rectangle.getPosition().y << std::endl;
		std::cout << player->hitbox.getPosition().x << " " << player->hitbox.getPosition().x << std::endl;
		std::cout << "Player was hit by arrow" << std::endl;*/
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
