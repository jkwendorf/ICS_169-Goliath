#include "GameState.h"
#include "PhysicsManager.h"

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
	delete currentScreen;
	delete nextScreen;
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
