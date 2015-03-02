#include "LevelSelectState.h"
#include "LoadingState.h"
#include "Global.h"
#include "StateManager.h"

LevelSelectState::LevelSelectState(void)
	: isPressedUp(false), isPressedDown(false), isRightPressed(false), isLeftPressed(false), inputCoolDown(0.25)
{
	f = new sf::Font();
	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/4, SCREEN_HEIGHT/8 + 50), 4, 15, sf::Vector2f(200, 66), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		
		// JW: We may want to have this be automated, so whenever the designers add a level to the Levels.xml, we'll create a new button

		for (int level = 1; level <= Global::GetInstance().levelInfo.size(); level++)
		{
			int numRooms = Global::GetInstance().levelInfo.at("Level " + std::to_string(level)).levelSize;
			for (int room = 1; room <= numRooms; room++)
			{
				if(Global::GetInstance().roomSizes["Level" + std::to_string(level) + "Room" + std::to_string(room)].open || Global::GetInstance().unlockAllRooms)
					bM->createButton("Level " + std::to_string(level) + "-" + std::to_string(room), [=] {StateManager::getInstance().addState(TRANSITION, new LoadingState(level, room), true);});
			}
		}
	}

	bg.setTexture(*TextureManager::GetInstance().retrieveTexture("LevelSelect"));

	shouldQuit = false;
}


LevelSelectState::~LevelSelectState(void)
{
}

void LevelSelectState::DeleteState()
{
	delete f;

	if(bM)
		delete bM;
}

void LevelSelectState::update(float deltaTime, sf::RenderWindow& window)
{
	if(inputCoolDown <= 0)
	{
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -75) && !isPressedUp)
		{
			bM->scrollUp();
			isPressedUp = true;
		}
		else if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > -75) && isPressedUp)
			isPressedUp = false;
	
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 75) &&!isPressedDown)
		{
			bM->scrollDown();
			isPressedDown = true;
		}
		else if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 75) && isPressedDown)
			isPressedDown = false;

		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -75) && !isLeftPressed)
		{
			bM->scrollLeft();
			isLeftPressed = true;
		}
		else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Joystick::getAxisPosition(0, sf::Joystick::X) > -75 && isLeftPressed)
			isLeftPressed = false;
	
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 75) && !isRightPressed)
		{
			bM->scrollRight();
			isRightPressed = true;
		}
		else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Joystick::getAxisPosition(0, sf::Joystick::X) < 75 && isRightPressed)
			isRightPressed = false;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Joystick::isButtonPressed(0, 0))
			bM->pressSelectedButton();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 1))
		{
			bM->resetSelectedButton();
			StateManager::getInstance().changeToState(MAIN_MENU, false);
		}
	}
	else
	{
		inputCoolDown -= deltaTime;
	}
}

void LevelSelectState::draw(sf::RenderWindow& window)
{
	sf::View v = window.getView();
	v.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(v);
	window.draw(bg);
	bM->draw(window);
}

void LevelSelectState::handleEvent(sf::Event event)
{}

void LevelSelectState::loadContent()
{
	if(bM)
		delete bM;
	bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/4, SCREEN_HEIGHT/8), 4, 15, sf::Vector2f(200, 66), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		
	// JW: We may want to have this be automated, so whenever the designers add a level to the Levels.xml, we'll create a new button

	for (int level = 1; level <= Global::GetInstance().levelInfo.size(); level++)
	{
		int numRooms = Global::GetInstance().levelInfo.at("Level " + std::to_string(level)).levelSize;
		for (int room = 1; room <= numRooms; room++)
		{
			if(Global::GetInstance().roomSizes["Level" + std::to_string(level) + "Room" + std::to_string(room)].open || Global::GetInstance().unlockAllRooms)
				bM->createButton("Level " + std::to_string(level) + "-" + std::to_string(room), [=] {StateManager::getInstance().addState(TRANSITION, new LoadingState(level, room), true);});
		}
	}
}

void LevelSelectState::unloadContent()
{
	inputCoolDown = 0.25;
}

void LevelSelectState::setToQuit()
{
	shouldQuit = true;
}