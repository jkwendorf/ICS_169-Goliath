#pragma once
#include "State.h"
#include "ButtonManager.h"
#include "Global.h"
#include "StateManager.h"
#include "PopOut.h"

class PauseGameState : public State
{
public:
	PauseGameState(void);
	virtual ~PauseGameState(void);

	void DeleteState();
	void update(float deltaTime, sf::RenderWindow& window);
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
	sf::Text pauseText;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	bool isPressedUp, isPressedDown, saved, backgroundUpdated;
};

