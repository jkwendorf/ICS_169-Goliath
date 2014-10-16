#pragma once
#include "State.h"

class MainMenuState : public State
{
public:
	MainMenuState(void);
	~MainMenuState(void);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void loadContent();
	void unloadContent();

private:
};

