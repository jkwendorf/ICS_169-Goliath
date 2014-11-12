#include "StateManager.h"

StateManager::StateManager(void)
{
	currentState = new GameState();
	currentState->loadContent();
}

StateManager::~StateManager(void)
{
	if(currentState != NULL)
	{
		currentState->DeleteState();
		delete currentState;
	}
	if(nextState != NULL)
	{
		nextState->DeleteState();
		delete nextState;
	}
}

void StateManager::changeToState(StateEnum state)
{
	switch(state)
	{
	case MAIN_MENU:
		nextState = new MainMenuState();
		break;
	case GAME:
		nextState = new GameState();
		break;
	case END_GAME:
		nextState = new EndGameState();
		break;
	//case TRANSITION:
		//break;
	default:
		nextState = new GameState();
		break;
	}

	loadState();
	unloadState();

	delete currentState;
	currentState = nextState;
	nextState = NULL;
}

void StateManager::loadState()
{
	nextState->loadContent();
}

void StateManager::unloadState()
{
	currentState->unloadContent();
}

void StateManager::update(float deltaTime)
{
	currentState->update(deltaTime);
}

void StateManager::draw(sf::RenderWindow& window)
{
	currentState->draw(window);
}

void StateManager::handleEvent(sf::Event event)
{
	currentState->handleEvent(event);
}