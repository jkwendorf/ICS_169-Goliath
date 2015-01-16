#include "PauseGameState.h"
#include "StateManager.h"

PauseGameState::PauseGameState(void)
	: isPressedUp(false), isPressedDown(false)
{
	f = new sf::Font();
	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/4 - 33), 15, sf::Vector2f(200, 66), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		bM->createButton("Resume", [] {StateManager::getInstance().changeToState(GAME, true);});
		bM->createButton("Save Game", [] {});
		bM->createButton("Options", [] {});
		bM->createButton("Quit", [&] {setToQuit();});
		//bM->createButton("Quit", [&] {StateManager::getInstance().changeToState(MAIN_MENU, true);});
	}

	shouldQuit = false;
}

PauseGameState::~PauseGameState(void)
{

}

void PauseGameState::DeleteState()
{
	delete f;

	if(bM)
		delete bM;
}

void PauseGameState::update(float deltaTime)
{
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -25) && !isPressedUp)
	{
		bM->scrollUp();
		isPressedUp = true;
	}
	else if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > -25) && isPressedUp)
		isPressedUp = false;
	
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 25) &&!isPressedDown)
	{
		bM->scrollDown();
		isPressedDown = true;
	}
	else if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 25) && isPressedDown)
		isPressedDown = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Joystick::isButtonPressed(0, 0))
		bM->pressSelectedButton();

	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 7))
	{
		StateManager::getInstance().changeToState(GAME, true);
	}*/
}

void PauseGameState::draw(sf::RenderWindow& window)
{
	sf::View v = window.getView();
	v.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(v);

	bM->draw(window);
}

void PauseGameState::handleEvent(sf::Event event)
{}

void PauseGameState::loadContent()
{

}

void PauseGameState::unloadContent()
{

}

void PauseGameState::setToQuit()
{
	shouldQuit = true;
}