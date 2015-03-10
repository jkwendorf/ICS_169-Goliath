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
#include "Camera.h"
#include "LevelStruct.h"

enum GoliathSoundEnum
{
	STOMP1 = 0,
	STOMP2 = 1,
	STOMP3 = 2,
	HURT1 = 3,
	HURT2 = 4,
	DOWNED = 5,
	GROWL1 = 6,
	GROWL2 = 7
};

class Level : public BaseGameScreen
{
private:
	bool changeScreen;
	float loading, introTimer;
	int levelNum;
	LevelStruct levelInfo;
	std::vector<std::shared_ptr<Enemy>> enemyList;
	std::vector<Tile*> arrowTileList;
	std::list<Tile*> destructTileList;
	std::list<Tile*> hitPointTileList;
	std::list<Tile> hitPointCopy;
	Player p;
	Room* currentRoom;
	sf::View view;
	//sf::RenderWindow win;
	sf::Sprite loadingSprite;
	sf::Sprite description;
	sf::Text introDescription;
	float arrowCool;
	float growlPlay;

	CollisionManager* collisionManager;
	InputManager inputManager;
	EnemyAI enemyAI;
	std::vector<Projectile*> arrows;
	Camera camera;
	sf::Sound goliathSound[8];

	bool arrowsCanFire;
	bool levelStart;
	bool screenShake;
	int shakeOffset;

	void viewCheck();
	void playerCheck();
	void changeRoom();
	void CleanUp();
	void setArrowTileArrows();
	void checkDestructableTiles();
	void checkHitPointTilesForDmg(float deltaTime);

	void loadSounds();
	void playHurtSound();
	void playStompSound();
	void playGrowlSound();

	bool checkHitPoints();
	void resetHitPoints();

	sf::Vector2f viewChangeOffset;
	float screenShakeDuration;
	float screenShakeCooldown, currentScreenShakeCooldown;

public:
	Level();
	Level(int levelNumber, int roomNumber);
	virtual ~Level(void);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void shakeScreen(float duration, int shakeOffset);
	void DeleteLevel();
	bool CheckChangeScreen();
	//checking if particle works
	Particle particle;
	ParticleEmitter particleEmitter, coneEmitter;
	float fixedTime;
	
};