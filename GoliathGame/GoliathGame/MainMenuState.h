#pragma once
#include "State.h"
#include "ButtonManager.h"
#include "Global.h"
#include "StateManager.h"

class MainMenuState : public State
{
public:
	MainMenuState(void);
	virtual ~MainMenuState(void);

	void DeleteState();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();

private:
	ButtonManager* bM;
	sf::Font* f;
	bool isPressedUp, isPressedDown;
};

