#pragma once
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "Player.h"
#include "Tile.h"
#include "Enemy.h"
#include <memory>


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	bool playerCollisionDetection(BaseObject* p);
	
	void setNearByTiles(std::vector<Tile> tiles);
	void setGrapplableTiles(std::vector<Tile> tiles);
	bool hookCollisionDetection(HookShot hs);
	Tile getHookedTile(HookShot hs);
	
	Tile getCollidedTile(BaseObject p);
	bool tileBelowCharacter(BaseObject* p);
	bool wallBlockingCharacter(BaseObject* p);
	int numTilesNear(BaseObject p);

	void checkPlayerBulletToEnemies(Projectile p[], Enemy* enemy);
	void checkPlayerSwordToEnemies(Sword s, Enemy* enemy);

	void checkEnemyBulletToEnemies(Projectile p[], Player* player);
	void checkEnemySwordToEnemies(Sword s, Player* player);

private:
	std::vector<Tile> tileList;
	std::vector<Tile> grapplableTileList;
};