#pragma once

#include "State.h"
#include "Global.h"

class LoadingState : public State
{
public:
	LoadingState(int level, int room);
	LoadingState();
	virtual ~LoadingState(void);

	void DeleteState();
	void update(float deltaTime, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();
	void setToQuit();

private:
	sf::Font* f;
	sf::Text t;
	bool isPressedUp, isPressedDown, isRightPressed, isLeftPressed;
	float inputCoolDown;
	int levelNumber, roomNumber;
	float loadTime;
};
