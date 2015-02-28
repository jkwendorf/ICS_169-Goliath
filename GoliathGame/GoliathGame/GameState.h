#pragma once
#include "State.h"
#include "InputManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Section.h"
#include "Global.h"
#include "Room.h"
#include "CollisionManager.h"
#include "Level.h"
#include "BaseGameScreen.h"

enum SCREENENUM
{
	TOWN,
	LEVEL,
	BOSS
};

class GameState : public State
{
public:
	GameState(int levelNum, int roomNumber);
	virtual ~GameState(void);
	void DeleteState();
	void update(float deltaTime, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();
	void setToQuit();

private:
	BaseGameScreen* currentScreen;
	BaseGameScreen* nextScreen;
	SCREENENUM screen;
	bool firstLoop;

};

