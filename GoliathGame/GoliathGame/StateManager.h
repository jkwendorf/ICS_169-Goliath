#pragma once

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameState.h"
#include "PauseGameState.h"
#include "LevelSelectState.h"
#include "ControlsState.h"

enum StateEnum
{
	MAIN_MENU,
	CONTROLS,
	GAME,
	TRANSITION,
	PAUSE_GAME,
	LEVEL_SELECT,
	END_GAME
};

class StateManager
{
public:
	static StateManager& getInstance() 
	{
		 static StateManager instance;
		 return instance;
	}

	void addState(StateEnum state, State* s);
	void addState(StateEnum state, State* s, bool makeCurrent);
	void deleteState(StateEnum state);
	void changeToState(StateEnum state, bool deleteCurrentState);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	State* getCurrentState();
	bool shouldQuit();
	void DeleteAllStates();
	bool shouldResetTime();
	void setTimeReset(bool reset);

private:
	StateManager(void) {};
	~StateManager(void) {};
	StateManager(StateManager const&);
	StateManager& operator =(StateManager const&);

	std::map<StateEnum, State*> stateMap;
	State* currentState;
	StateEnum currentStateEnum;
	bool resetTime;
};

