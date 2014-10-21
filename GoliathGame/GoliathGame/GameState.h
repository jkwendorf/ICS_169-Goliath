#pragma once
#include "State.h"

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

private:
	sf::RectangleShape r;
};

