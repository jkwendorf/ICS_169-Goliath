#pragma once

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "Global.h"
#include "BaseGameScreen.h"
#include "Room.h"
#include "Enemy.h"

class Level : public BaseGameScreen
{
private:
	int levelNum, maxRooms;
	Player p;
	std::vector<Enemy*> enemyList;
	Room* currentRoom;
	sf::View view;
	sf::RenderWindow win;
	sf::Sprite background;

	CollisionManager* collisionManager;
	InputManager* inputManager;

	void viewCheck();
	void playerCheck();
	void changeRoom();
public:
	Level();
	Level(int levelNumber);
	~Level(void);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

};