#include "ControlsState.h"
#include "TextureManager.h"
#include "StateManager.h"

ControlsState::ControlsState(void)
{
	shouldQuit = false;
	controls.setTexture(*TextureManager::GetInstance().retrieveTexture("Controls"));
}

ControlsState::~ControlsState(void)
{

}

void ControlsState::DeleteState()
{

}

void ControlsState::update(float deltaTime, sf::RenderWindow& window)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 1))
	{
		StateManager::getInstance().changeToState(MAIN_MENU, false);
	}
}

void ControlsState::draw(sf::RenderWindow& window)
{
	sf::View v = window.getView();
	v.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(v);

	window.draw(controls);
}

void ControlsState::handleEvent(sf::Event event)
{}

void ControlsState::loadContent()
{

}

void ControlsState::unloadContent()
{

}

void ControlsState::setToQuit()
{
	shouldQuit = true;
}