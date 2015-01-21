#pragma once

#include "State.h"
#include "ButtonManager.h"

class LevelSelectState : public State
{
public:
	LevelSelectState(void);
	virtual ~LevelSelectState(void);

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
	bool isPressedUp, isPressedDown, isRightPressed, isLeftPressed;
	float inputCoolDown;
};

