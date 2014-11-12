#pragma once
#include "State.h"

class MainMenuState : public State
{
public:
	MainMenuState(void);
	~MainMenuState(void);

	void DeleteState();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();

private:
};

