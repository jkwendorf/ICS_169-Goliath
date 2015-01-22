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


class Level : public BaseGameScreen
{
private:
	bool changeScreen;
	float loading;
	int levelNum, maxRooms;
	std::vector<std::shared_ptr<Enemy>> enemyList;
	Player p;
	Room* currentRoom;
	sf::View view;
	sf::RenderWindow win;
	sf::Sprite background, loadingSprite;

	CollisionManager* collisionManager;
	InputManager inputManager;
	EnemyAI enemyAI;

	void viewCheck();
	void playerCheck();
	void changeRoom();
	void CleanUp();
public:
	Level();
	Level(int levelNumber, int roomNumber);
	virtual ~Level(void);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void DeleteLevel();
	void CheckChangeScreen(BaseGameScreen* newScreen);
};