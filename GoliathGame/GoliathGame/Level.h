#pragma once

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "Global.h"
#include "BaseGameScreen.h"
#include "Room.h"
#include "Enemy.h"
#include <memory>

class Level : public BaseGameScreen
{
private:
	float loading;
	int levelNum, maxRooms;
	Player p;
	std::vector<std::unique_ptr<Enemy>> enemyList;
	Room* currentRoom;
	sf::View view;
	sf::RenderWindow win;
	sf::Sprite background, loadingSprite;

	CollisionManager* collisionManager;
	InputManager* inputManager;

	void viewCheck();
	void playerCheck();
	void changeRoom();
	void CleanUp();
public:
	Level();
	Level(int levelNumber);
	~Level(void);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void DeleteLevel();
};