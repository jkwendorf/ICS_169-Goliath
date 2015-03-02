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
	void update(float deltaTime, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void loadContent();
	void unloadContent();
	void setToQuit();

private:
	ButtonManager* bM;
	sf::Font* f;
	sf::Sound* bgMusic;
	bool played;
	bool isPressedUp, isPressedDown;
	float inputCoolDown;
	sf::Sprite bg;
};

