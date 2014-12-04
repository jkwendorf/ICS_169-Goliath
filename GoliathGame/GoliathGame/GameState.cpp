#include "GameState.h"
#include "PhysicsManager.h"

GameState::GameState(void)
	:currentScreen(new Level(1)), screen(LEVEL)
{

}

GameState::~GameState(void)
{
	//delete currentRoom;
	//delete collisionManager;
}

void GameState::DeleteState()
{
	std::cout << "Deleting the state" << std::endl;
	currentScreen->DeleteLevel();
	delete currentScreen;
	/*
	std::cout << "Calling GameState destructor" << std::endl;
	delete collisionManager;
	delete currentRoom;
	*/
}

void GameState::update(float deltaTime)
{
	currentScreen->update(deltaTime);
	if(currentScreen->CheckChangeScreen())
	{
		
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
