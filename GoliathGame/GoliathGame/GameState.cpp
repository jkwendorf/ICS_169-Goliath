#include "GameState.h"
#include "PhysicsManager.h"
#include "StateManager.h"

GameState::GameState(int levelNum, int roomNumber)
	:currentScreen(new Level(levelNum, roomNumber)), nextScreen(NULL), screen(LEVEL)
{
	shouldQuit = false;
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

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 7))
	{
		StateManager::getInstance().addState(PAUSE_GAME, new PauseGameState(), true);
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

void GameState::setToQuit()
{
	shouldQuit = true;
}