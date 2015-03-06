#include "PauseGameState.h"
#include "StateManager.h"

PauseGameState::PauseGameState(void)
	: isPressedUp(false), isPressedDown(false), saved(false), pO(new PopOut()), backgroundUpdated(false)
{
	if(!backgroundTexture.create(SCREEN_WIDTH + 1, SCREEN_HEIGHT+ 1))
		backgroundUpdated = true;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor(sf::Color(64, 64, 64, 255));

	f = new sf::Font();
	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/4), 15, sf::Vector2f(200, 66), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		bM->createButton("Resume", [] {StateManager::getInstance().changeToState(GAME, true);});
		bM->createButton("Save Game", [&] {changeSaved();});
		bM->createButton("Options", [] {});
		//bM->createButton("Quit", [&] {setToQuit();});
		bM->createButton("Quit", [&] {
			StateManager::getInstance().deleteState(GAME);
			StateManager::getInstance().changeToState(MAIN_MENU, true);});

		pauseText.setString("Paused");
		pauseText.setFont(*f);
		pauseText.setCharacterSize(72);
		pauseText.setColor(sf::Color(128, 128, 128, 255));
		pauseText.setOrigin(pauseText.getGlobalBounds().width/2, pauseText.getGlobalBounds().height/2);
		pauseText.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/8);
	}

	shouldQuit = false;
}

PauseGameState::PauseGameState(sf::RenderWindow& window)
	: isPressedUp(false), isPressedDown(false), saved(false), pO(new PopOut()), backgroundUpdated(false)
{
	if(backgroundTexture.create(SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1))
		backgroundTexture.update(window);
	backgroundUpdated = true;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor(sf::Color(64, 64, 64, 255));

	f = new sf::Font();
	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/4), 15, sf::Vector2f(200, 66), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		bM->createButton("Resume", [] {StateManager::getInstance().changeToState(GAME, true);});
		bM->createButton("Save Game", [&] {changeSaved();});
		bM->createButton("Options", [] {});
		//bM->createButton("Quit", [&] {setToQuit();});
		bM->createButton("Quit", [&] {
			StateManager::getInstance().deleteState(GAME);
			StateManager::getInstance().changeToState(MAIN_MENU, true);});

		pauseText.setString("Paused");
		pauseText.setFont(*f);
		pauseText.setCharacterSize(72);
		pauseText.setColor(sf::Color(128, 128, 128, 255));
		pauseText.setOrigin(pauseText.getGlobalBounds().width/2, pauseText.getGlobalBounds().height/2);
		pauseText.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/8);
	}

	shouldQuit = false;
}

PauseGameState::~PauseGameState(void)
{

}

void PauseGameState::DeleteState()
{
	delete f;
	delete pO;
	if(bM)
		delete bM;

}

void PauseGameState::update(float deltaTime, sf::RenderWindow& window)
{
	if(!backgroundUpdated)
	{
		backgroundUpdated = true;
		backgroundTexture.update(window);
	}

	if(!pO->checkActive())
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
	}
	else
	{
		pO->update(deltaTime);
	}
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

	window.draw(backgroundSprite);
	window.draw(pauseText);

	if(!pO->checkActive())
		bM->draw(window);
	else
		pO->draw(window);
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

void PauseGameState::changeSaved()
{
	if(!saved)
	{
		Global::GetInstance().SavePlayer();
		delete pO;
		pO = new PopOut(std::string("Game has been saved"), [&] {changeSaved();});
	}
	saved != saved;
}