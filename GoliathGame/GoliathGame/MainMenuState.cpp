#include "MainMenuState.h"
#include "StateManager.h"

MainMenuState::MainMenuState(void)
	: isPressedUp(false), isPressedDown(false)
	//:play(new Button(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/3), TextureManager::GetInstance().retrieveTexture("PlayButton"), m.changeToState(GAME)))
{
	f = new sf::Font();
	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		bM = new ButtonManager(sf::Vector2f(100, 100), 25, sf::Vector2f(200, 66), TextureManager::GetInstance().retrieveTexture("ButtonTest"), f); 
		bM->createButton("Play Game", [] {StateManager::getInstance().changeToState(GAME, false);});
		bM->createButton("Help", [] {std::cout << "HI" << std::endl;});
		bM->createButton("Options", [] {});
		bM->createButton("Quit", [] {});
	}
}

MainMenuState::~MainMenuState(void)
{

}

void MainMenuState::DeleteState()
{
	delete f;

	if(bM)
		delete bM;
}

void MainMenuState::update(float deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		StateManager::getInstance().changeToState(GAME, false);
	}
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::O) && !isPressed)
	{
 		StateManager::getInstance().deleteState(GAME);
		StateManager::getInstance().addState(GAME, new GameState());
		isPressed = true;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		isPressed = false;*/

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isPressedUp)
	{
		bM->scrollUp();
		isPressedUp = true;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		isPressedUp = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&!isPressedDown)
	{
		bM->scrollDown();
		isPressedDown = true;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		isPressedDown = false;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		bM->pressSelectedButton();
	}
}

void MainMenuState::draw(sf::RenderWindow& window)
{
	sf::View v = window.getView();
	v.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(v);

	bM->draw(window);
}

void MainMenuState::handleEvent(sf::Event event)
{}

void MainMenuState::loadContent()
{

}

void MainMenuState::unloadContent()
{

}