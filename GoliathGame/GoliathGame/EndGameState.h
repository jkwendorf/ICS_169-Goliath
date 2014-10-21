#pragma once
#include "State.h"

class EndGameState : public State
{
public:
	EndGameState(void);
	~EndGameState(void);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();

private:
};