#pragma once
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "Player.h"
#include "Tile.h"
#include "Enemy.h"
#include "Subject.h"
#include "PlayerInventory.h"
#include <memory>

class Player;

class CollisionManager : public Subject
{
public:
	CollisionManager();
	~CollisionManager();
	bool playerCollisionDetection(BaseObject* p);
	void checkTreasure(Player& p);
	
	void setNearByTiles(std::vector<Tile*> tiles);
	void setGrapplableTiles(std::vector<Tile*> tiles);
	bool hookCollisionDetection(HookShot hs);
	Tile* getHookedTile(HookShot hs);
	
	Tile* getCollidedTile(BaseObject p);
	Tile getNearestGrappleTile(BaseObject p);
	bool tileBelowCharacter(BaseObject* p);
	bool wallBlockingCharacter(BaseObject* p);
	int numTilesNear(BaseObject p);

	void checkPlayerBulletToEnemies(Projectile p, Enemy* enemy);
	void checkPlayerSwordToEnemies(Sword s, Enemy* enemy);

	void checkEnemyBulletToPlayer(Projectile p, Player* player);
	void checkEnemySwordToPlayer(Sword s, Player* player);

	bool playerSwordCollideWithTile(Sword s, Tile* t);

	bool isGrappleListEmpty();

	bool checkIfEnemyInRange(Projectile p, Player* player);
	bool hShotHitNonGrappleTile(HookShot hs);
private:
	std::vector<Tile*> tileList;
	std::vector<Tile*> grapplableTileList;
};