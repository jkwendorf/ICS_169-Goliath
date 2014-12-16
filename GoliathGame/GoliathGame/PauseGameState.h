#pragma once
#include "State.h"
#include "ButtonManager.h"
#include "Global.h"
#include "StateManager.h"

class PauseGameState : public State
{
public:
	PauseGameState(void);
	virtual ~PauseGameState(void);

	void DeleteState();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();
	void setToQuit();

private:
	ButtonManager* bM;
	sf::Font* f;
	bool isPressedUp, isPressedDown;
};

