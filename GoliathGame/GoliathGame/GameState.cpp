#include "GameState.h"
#include "PhysicsManager.h"
#include "StateManager.h"

GameState::GameState(int levelNum, int roomNumber)
	:currentScreen(new Level(levelNum, roomNumber)), nextScreen(NULL), screen(LEVEL), firstLoop(true)
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

void GameState::update(float deltaTime, sf::RenderWindow& window)
{
	if(!firstLoop)
	{
		currentScreen->update(deltaTime);
		if(currentScreen->CheckChangeScreen())
		{
			StateManager::getInstance().changeToState(MAIN_MENU, true);
			StateManager::getInstance().deleteState(GAME);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 7))
		{
			Global::GetInstance().ControllerVibrate();
			StateManager::getInstance().addState(PAUSE_GAME, new PauseGameState(window), true);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			Global::GetInstance().ControllerVibrate(0, 50);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			Global::GetInstance().ControllerVibrate();
	}
	else
		firstLoop = false;
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