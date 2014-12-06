#pragma once
#include "State.h"
#include "Button.h"
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
	//Button* play, help, credits;
	bool isPressed;
};

