#include "StateManager.h"

// Adds a state into the StateManager, but can also be used to set the added state as the current state
void StateManager::addState(StateEnum state, State* s, bool makeCurrent)
{
	stateMap.insert(std::make_pair(state, s));

	if(makeCurrent)
	{
		if (currentState)
			currentState->unloadContent();

		currentState = s;
		currentStateEnum = state;
		currentState->loadContent();
		setTimeReset(true);
	}
}

// Adds a state into the StateManager
void StateManager::addState(StateEnum state, State* s)
{
	addState(state, s, false);
}

// Deletes a selected state from the StateManager
void StateManager::deleteState(StateEnum state)
{
	auto iter = stateMap.begin();
	iter = stateMap.find(state);
	
	if(iter != stateMap.end() && stateMap.size() != 1)
	{
		iter->second->DeleteState();
		delete iter->second;

		// Safeguard in case someone deletes the current state
		if (currentState == iter->second) 
		{
			currentState = stateMap.begin()->second;
			currentStateEnum = stateMap.begin()->first;
		}

		stateMap.erase(iter);
	}
}

// Loads a new state to be displayed, can also delete the current state
void StateManager::changeToState(StateEnum state, bool deleteCurrentState)
{
	auto iter = stateMap.begin();
	iter = stateMap.find(state);

	if(iter != stateMap.end())
	{
		if (currentState)
			currentState->unloadContent();

		if (deleteCurrentState)
		{
			auto current = stateMap.begin();
			current = stateMap.find(currentStateEnum);
			
			currentState->DeleteState();
			delete currentState;
			stateMap.erase(current);
		}

		currentState = iter->second;
		currentStateEnum = state;
		currentState->loadContent();
	}
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

State* StateManager::getCurrentState()
{
	return currentState;
}

void StateManager::DeleteAllStates()
{
	auto iter = stateMap.begin();
	while(iter != stateMap.end())
	{
		if(iter->second != nullptr)
		{
			iter->second->DeleteState();
			delete iter->second;
			
		}
		iter++;
	}
	stateMap.clear();
	std::cout << "deleting all remaining states" << std::endl;
}

bool StateManager::shouldQuit()
{
	return currentState->shouldQuit;
}

bool StateManager::shouldResetTime()
{
	return resetTime;
}

void StateManager::setTimeReset(bool reset)
{
	resetTime = reset;
}