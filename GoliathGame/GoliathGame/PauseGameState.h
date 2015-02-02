#pragma once
#include "State.h"
#include "ButtonManager.h"
#include "Global.h"
#include "StateManager.h"
#include "PopOut.h"s

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
	void changeSaved();

private:
	ButtonManager* bM;
	PopOut* pO;
	sf::Font* f;
	bool isPressedUp, isPressedDown, saved;
};

