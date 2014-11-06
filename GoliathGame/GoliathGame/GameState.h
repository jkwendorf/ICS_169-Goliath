#pragma once
#include "State.h"
#include "InputManager.h"
#include "Player.h"
<<<<<<< HEAD
#include "Section.h"
#include "Global.h"
=======
#include "Level.h"
>>>>>>> 819790a0b5f26e4b8bfd7f7e8e91a2ee419ec3d3

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
<<<<<<< HEAD
	Section s;
	sf::View view;
	sf::RenderWindow win;
	sf::Vector2f playerPos;
	void viewCheck();
=======
	Level s;
>>>>>>> 819790a0b5f26e4b8bfd7f7e8e91a2ee419ec3d3
};

