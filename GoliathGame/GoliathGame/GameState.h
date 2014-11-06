#pragma once
#include "State.h"
#include "InputManager.h"
#include "Player.h"
#include "Section.h"
#include "Global.h"

class GameState : public State
{
public:
	GameState(void);
	~GameState(void);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();

	Player p;

private:
	InputManager inputManager;
	Section s;
	sf::View view;
	sf::RenderWindow win;
	sf::Vector2f playerPos;
	void viewCheck();
};

