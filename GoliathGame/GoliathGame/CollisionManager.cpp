#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::hookCollisionDetection(HookShot hs)
{
	for(Tile b : grapplableTileList)
	{
		//b->sprite.setColor(sf::Color::Red);
		if(b.intersects(hs.sprite.getGlobalBounds()) && b.getGrappleable())
			return true;
	}
	return false;
}

bool CollisionManager::playerCollisionDetection(BaseObject* p)
{
	for(Tile b : tileList)
	{
		//std::cout << "(" << b.left << "," << b.top << ")";
		//std::cout << "(" << p->sprite.getGlobalBounds().left << "," << p->sprite.getGlobalBounds().top << ")" << std::endl;
		
		if(b.intersects(p->sprite.getGlobalBounds()))
			return true;
	}
	//std::cout << "\n\n\n\n";
	return false;
}


Tile CollisionManager::getCollidedTile(BaseObject p)
{
	for(Tile b : tileList)
		if(b.intersects(p.sprite.getGlobalBounds()))
			return b;
	return Tile(sf::Vector2f(-1,-1), sf::Vector2f(0,0), -999);
}

void CollisionManager::setNearByTiles(std::vector<Tile> tiles)
{
	tileList = tiles;
}

void CollisionManager::setGrapplableTiles(std::vector<Tile> tiles)
{
	grapplableTileList = tiles;
}

bool CollisionManager::tileBelowCharacter(BaseObject* p)
{
	float left = p->sprite.getPosition().x - p->sprite.getGlobalBounds().width/2,
		right = p->sprite.getPosition().x + p->sprite.getGlobalBounds().width/2;

	for(Tile b : tileList)
	{
		//if(b->intersects(p->sprite.getGlobalBounds()) && b->top >= p->sprite.getPosition().y)
		if(b.top >= p->sprite.getPosition().y + p->sprite.getGlobalBounds().height/2)
			if((b.left <= left && b.left + b.width >= left) ||
				(b.left <= right && b.left + b.width >= right))
				return true;
	}
	return false;
}

bool CollisionManager::wallBlockingCharacter(BaseObject* p)
{
	float top = ceil(p->sprite.getPosition().y - p->sprite.getGlobalBounds().height/2);
	for(Tile b: tileList)
	{
		if(b.intersects(p->sprite.getGlobalBounds()))
		{
			if(b.top + b.height > top)
 				return true;
		}
	}
	return false;
}

int CollisionManager::numTilesNear(BaseObject p)
{
	return tileList.size();
}

Tile CollisionManager::getHookedTile(HookShot hs)
{
	for(Tile b : grapplableTileList)
	{
		if(b.intersects(hs.sprite.getGlobalBounds()) && b.getGrappleable())
			return b;
	}
	return Tile(sf::Vector2f(-1,-1), sf::Vector2f(0,0), -999);
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

void CollisionManager::checkEnemyBulletToEnemies(Projectile p, Player* player)
{
	//for(int x = 0; x < 3; x++)
	
		if(sqrt(pow(p.sprite.getPosition().x - player->sprite.getPosition().x, 2) + 
			pow(p.sprite.getPosition().y - player->sprite.getPosition().y, 2)) < 50 && p.moving)
		{
			player->health -= p.damage;
			p.moving = false;
			//Convert to single projectile
			//check if it collides with wall and make it disappear when it collides
		}
}

void CollisionManager::checkEnemySwordToEnemies(Sword s, Player* player)
{
	if(sqrt(pow(s.hitBox.getPosition().x - player->sprite.getPosition().x, 2) + 
		pow(s.hitBox.getPosition().y - player->sprite.getPosition().y, 2)) < 75 && s.attacking)
	{
		player->health -= s.damage;
	}
}