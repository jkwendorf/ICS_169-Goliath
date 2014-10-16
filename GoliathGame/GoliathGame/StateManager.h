#pragma once

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameState.h"

enum StateEnum
{
	MAIN_MENU,
	GAME,
	TRANSITION,
	END_GAME
};

class StateManager
{
public:
	StateManager(void);
	~StateManager(void);

	void changeToState(StateEnum state);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	void loadState();
	void unloadState();

	State* currentState;
	State* nextState;
};

