#pragma once

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "Global.h"
#include "BaseGameScreen.h"
#include "Room.h"
#include "Enemy.h"
#include "EnemyAI.h"
#include <memory>
#include "Town.h"
#include "JumpingState.h"
#include "IdleState.h"
#include "Tile.h"
#include "Particle.h"
#include "ParticleEmitter.h"

class Level : public BaseGameScreen
{
private:
	bool changeScreen;
	float loading;
	int levelNum, maxRooms;
	std::vector<std::shared_ptr<Enemy>> enemyList;
	std::vector<Tile*> arrowTileList;
	std::list<Tile*> destructTileList;
	Player p;
	Room* currentRoom;
	sf::View view;
	//sf::RenderWindow win;
	sf::Sprite loadingSprite;
	float arrowCool;

	CollisionManager* collisionManager;
	InputManager inputManager;
	EnemyAI enemyAI;
	std::vector<Projectile*> arrows;

	bool arrowsCanFire;

	void viewCheck();
	void playerCheck();
	void changeRoom();
	void CleanUp();
	void setArrowTileArrows();
	void checkDestructableTiles();

	sf::Vector2f viewChangeOffset;
	float screenShakeDuration;
	float screenShakeCooldown, currentScreenShakeCooldown;

public:
	Level();
	Level(int levelNumber, int roomNumber);
	virtual ~Level(void);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void DeleteLevel();
	bool CheckChangeScreen();
	//checking if particle works
	Particle particle;
	ParticleEmitter particleEmitter;
	float fixedTime;
};