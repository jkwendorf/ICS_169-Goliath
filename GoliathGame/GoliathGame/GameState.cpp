#include "GameState.h"
#include "PhysicsManager.h"
#include "StateManager.h"

GameState::GameState(void)
	:currentScreen(new Level(1)), nextScreen(NULL), screen(LEVEL)
{

}

GameState::~GameState(void)
{
	DeleteState();
}

void GameState::DeleteState()
{
	if(currentScreen != nullptr)
	{
		delete currentScreen;
		currentScreen = nullptr;
	}
	if(nextScreen != nullptr)
	{
		delete nextScreen;
		nextScreen = nullptr;
	}
}

void GameState::update(float deltaTime)
{
	currentScreen->update(deltaTime);
	currentScreen->CheckChangeScreen(nextScreen);
	if(nextScreen)
	{
		delete currentScreen;
		currentScreen = nextScreen;
		nextScreen = NULL;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		StateManager::getInstance().changeToState(MAIN_MENU, false);
	}
}

void GameState::draw(sf::RenderWindow& window)
{
	currentScreen->draw(window);
}

void GameState::handleEvent(sf::Event event)
{

}

void GameState::loadContent()
{
	//currentRoom = new currentRoom(roomNum);
}

void GameState::unloadContent()
{
	//currentRoom* temp = currentRoom;
	//delete temp;
}
