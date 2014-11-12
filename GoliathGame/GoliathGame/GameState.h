#pragma once
#include "State.h"
#include "InputManager.h"
#include "Player.h"
#include "Section.h"
#include "Global.h"
#include "Level.h"
#include "CollisionManager.h"


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

	Player p;

private:
	InputManager inputManager;
	Level* level;
	sf::View view;
	sf::RenderWindow win;
	sf::Vector2f topLeft;
	void viewCheck();
	CollisionManager* collisionManager;
};

