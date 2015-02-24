#pragma once
#include "State.h"
#include "ButtonManager.h"

class EndGameState : public State
{
public:
	EndGameState(void);
	virtual ~EndGameState(void);

	void DeleteState();
	void update(float deltaTime, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();
	void setToQuit();

private:
	sf::Font* f;
	ButtonManager* bM;
	bool isUpPressed, isDownPressed;
};