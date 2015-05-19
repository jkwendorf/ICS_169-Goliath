#include "CreditsState.h"
#include "TextureManager.h"


CreditsState::CreditsState(void)
{
	shouldQuit = false;

	programmerLabel = sf::Text("Programmers", Global::GetInstance().font, 40);
	programmerLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
	programmerLabel.setOrigin(floor(programmerLabel.getLocalBounds().width/2), 0);
	programmerLabel.setPosition(SCREEN_WIDTH/4, 200);

	programmerList = sf::Text("Nathan Duong\nIsidro Gomez\nTyler Nutsathitya\nGrant Walker\nJonathan Wendorf", Global::GetInstance().font, 40);
	programmerList.setOrigin(floor(programmerList.getLocalBounds().width/2), 0);
	programmerList.setPosition(SCREEN_WIDTH/4, 250);
	
	designerLabel = sf::Text("Designers", Global::GetInstance().font, 40);
	designerLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
	designerLabel.setOrigin(floor(designerLabel.getLocalBounds().width/2), 0);
	designerLabel.setPosition(SCREEN_WIDTH/2, 200);

	designerList = sf::Text("Khai Nguyen\nCameron Rij\nRobert Skelton", Global::GetInstance().font, 40);
	designerList.setOrigin(floor(designerList.getLocalBounds().width/2), 0);
	designerList.setPosition(SCREEN_WIDTH/2, 250);
	
	artistLabel = sf::Text("Artists", Global::GetInstance().font, 40);
	artistLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
	artistLabel.setOrigin(floor(artistLabel.getLocalBounds().width/2), 0);
	artistLabel.setPosition((3*SCREEN_WIDTH)/4, 200);

	artistList = sf::Text("Catherine Africa\nRicky Chiu\nAlex Chung\nBrian Kimm\nLily Makela\nRyan Wauson\nSamuel Youn", Global::GetInstance().font, 40);
	artistList.setOrigin(floor(artistList.getLocalBounds().width/2), 0);
	artistList.setPosition((3*SCREEN_WIDTH)/4, 250);

	bg.setTexture(*TextureManager::GetInstance().retrieveTexture("MenuBG"));
	bg.setColor(sf::Color(64, 64, 64, 255));
}


CreditsState::~CreditsState(void)
{
}

void CreditsState::DeleteState()
{

}

void CreditsState::update(float deltaTime, sf::RenderWindow& window)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 1))
	{
		StateManager::getInstance().changeToState(MAIN_MENU, false);
	}
}

void CreditsState::draw(sf::RenderWindow& window)
{
	sf::View v = window.getView();
	v.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(v);

	window.draw(bg);
	window.draw(programmerLabel);
	window.draw(programmerList);
	window.draw(designerLabel);
	window.draw(designerList);
	window.draw(artistLabel);
	window.draw(artistList);
}

void CreditsState::handleEvent(sf::Event event)
{

}

void CreditsState::loadContent()
{

}

void CreditsState::unloadContent()
{

}

void CreditsState::setToQuit()
{
	shouldQuit = true;
}