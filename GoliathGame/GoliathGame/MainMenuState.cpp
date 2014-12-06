#include "MainMenuState.h"
#include "StateManager.h"

MainMenuState::MainMenuState(void)
	: isPressed(false)
	//:play(new Button(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/3), TextureManager::GetInstance().retrieveTexture("PlayButton"), m.changeToState(GAME)))
{
}

MainMenuState::~MainMenuState(void)
{
}

void MainMenuState::DeleteState()
{

}

void MainMenuState::update(float deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		StateManager::getInstance().changeToState(GAME, false);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::O) && !isPressed)
	{
 		StateManager::getInstance().deleteState(GAME);
		StateManager::getInstance().addState(GAME, new GameState());
		isPressed = true;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		isPressed = false;
}

void MainMenuState::draw(sf::RenderWindow& window)
{

}

void MainMenuState::handleEvent(sf::Event event)
{

}

void MainMenuState::loadContent()
{

}

void MainMenuState::unloadContent()
{

}