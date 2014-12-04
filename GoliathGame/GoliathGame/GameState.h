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
	GameState(void);
	~GameState(void);
	void DeleteState();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();

private:
	BaseGameScreen* currentScreen;
	SCREENENUM screen;

};

