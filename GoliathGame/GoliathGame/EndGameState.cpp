#include "EndGameState.h"
#include "StateManager.h"

EndGameState::EndGameState(void)
	:isUpPressed(false), isDownPressed(false)
{
	f = new sf::Font();
	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/4 - 33), 15, sf::Vector2f(200, 66), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		bM->createButton("Retry", [] {StateManager::getInstance().addState(GAME, new GameState(), true);});
		bM->createButton("Quit", [&] {setToQuit();});
	}
	
	shouldQuit = false;
}

EndGameState::~EndGameState(void)
{
}

void EndGameState::DeleteState()
{
	delete f;

	if(bM)
		delete bM;
}

void EndGameState::update(float deltaTime)
{
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -25) && !isUpPressed)
	{
		bM->scrollUp();
		isUpPressed = true;
	}
	else if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > -25) && isUpPressed)
		isUpPressed = false;
	
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 25) &&!isDownPressed)
	{
		bM->scrollDown();
		isDownPressed = true;
	}
	else if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 25) && isDownPressed)
		isDownPressed = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Joystick::isButtonPressed(0, 0))
		bM->pressSelectedButton();
}

void EndGameState::draw(sf::RenderWindow& window)
{
	sf::View v = window.getView();
	v.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(v);

	bM->draw(window);
}

void EndGameState::handleEvent(sf::Event event)
{

}

void EndGameState::loadContent()
{

}

void EndGameState::unloadContent()
{

}

void EndGameState::setToQuit()
{
	shouldQuit = true;
}