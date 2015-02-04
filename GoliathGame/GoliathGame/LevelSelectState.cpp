#include "LevelSelectState.h"
#include "Global.h"
#include "StateManager.h"

LevelSelectState::LevelSelectState(void)
	: isPressedUp(false), isPressedDown(false), isRightPressed(false), isLeftPressed(false), inputCoolDown(0.25)
{
	f = new sf::Font();
	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(SCREEN_WIDTH/4, SCREEN_HEIGHT/8), 4, 15, sf::Vector2f(200, 66), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		
		// JW: We may want to have this be automated, so whenever the designers add a level to the Levels.xml, we'll create a new button

		for (int level = 1; level <= Global::GetInstance().levelSizes.size(); level++)
		{
			int numRooms = Global::GetInstance().levelSizes.at("Level " + std::to_string(level));
			for (int room = 1; room <= numRooms; room++)
			{
				bM->createButton("Level " + std::to_string(level) + "-" + std::to_string(room), [=] {StateManager::getInstance().addState(GAME, new GameState(level, room), true);});
			}
		}
	}

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

void LevelSelectState::update(float deltaTime)
{
	if(inputCoolDown <= 0)
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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isLeftPressed)
		{
			bM->scrollLeft();
			isLeftPressed = true;
		}
		else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && isLeftPressed)
			isLeftPressed = false;
	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!isRightPressed)
		{
			bM->scrollRight();
			isRightPressed = true;
		}
		else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && isRightPressed)
			isRightPressed = false;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Joystick::isButtonPressed(0, 0))
			bM->pressSelectedButton();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 7))
		{
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

	bM->draw(window);
}

void LevelSelectState::handleEvent(sf::Event event)
{}

void LevelSelectState::loadContent()
{

}

void LevelSelectState::unloadContent()
{
	inputCoolDown = 0.25;
}

void LevelSelectState::setToQuit()
{
	shouldQuit = true;
}