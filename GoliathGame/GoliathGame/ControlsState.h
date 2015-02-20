#pragma once
#include "State.h"
#include "ButtonManager.h"
#include "Global.h"
#include "StateManager.h"

class ControlsState : public State
{
public:
	ControlsState(void);
	virtual ~ControlsState(void);

	void DeleteState();
	void update(float deltaTime, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();
	void setToQuit();

private:
	sf::Sprite controls;
};

