#pragma once
#include "State.h"
#include "ButtonManager.h"
#include "Global.h"
#include "StateManager.h"

class CreditsState : public State
{
public:
	CreditsState(void);
	virtual ~CreditsState(void);

	void DeleteState();
	void update(float deltaTime, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();
	void setToQuit();

private:
	sf::Text programmerLabel;
	sf::Text designerLabel;
	sf::Text artistLabel;
	sf::Text programmerList;
	sf::Text designerList;
	sf::Text artistList;
	sf::Sprite bg;
};

