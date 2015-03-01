#include "LoadingState.h"
#include "StateManager.h"

LoadingState::LoadingState(int level, int room) :
	levelNumber(level), roomNumber(room), loadTime(0.0f)
{
	f = new sf::Font();

	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		t.setString("LOADING...");
		t.setFont(*f);
		t.setCharacterSize(50);
		t.setPosition(520, 320);
	}
	shouldQuit = false;
}

LoadingState::LoadingState() : loadTime(0.0f), levelNumber(NULL), roomNumber(NULL)
{
	f = new sf::Font();

	if(f->loadFromFile("media/fonts/arial.ttf"))
	{
		t.setString("LOADING...");
		t.setFont(*f);
		t.setCharacterSize(50);
		t.setPosition(520, 320);
	}
	shouldQuit = false;
}
LoadingState::~LoadingState()
{
}

void LoadingState::DeleteState()
{
	delete f;
}

void LoadingState::update(float deltaTime, sf::RenderWindow& window)
{
	loadTime += deltaTime;
	if(loadTime > 1.0f)
	{
		if(levelNumber != NULL && roomNumber != NULL)
		{
			StateManager::getInstance().addState(GAME, new GameState(levelNumber, roomNumber), false);
		}
		StateManager::getInstance().changeToState(GAME, true);
	}
}

void LoadingState::draw(sf::RenderWindow& window)
{
	sf::View v = window.getView();
	v.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(v);
	window.draw(t);
}

void LoadingState::handleEvent(sf::Event event)
{}

void LoadingState::loadContent()
{

}

void LoadingState::unloadContent()
{
	inputCoolDown = 0.25;
}

void LoadingState::setToQuit()
{
	shouldQuit = true;
}

//once you load a level, return true and change it over