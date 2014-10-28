#include "GameState.h"

GameState::GameState(void)
{
	s.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));

	//r.setFillColor(sf::Color::Green);
	//r.setSize(sf::Vector2f(10, 10));
	//r.setPosition(sf::Vector2f(100, 100));

	//Code for player draw
	//p.draw(TextureManager::GetInstance().retrieveTexture("player"), 40, 23);
}

GameState::~GameState(void)
{
}

void GameState::update(float deltaTime)
{
	//Update for Player still needs to be fleshed out
	//p.update();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		//r.move(0.f, -100*deltaTime);
		s.move(0.f, -100*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//r.move(0.f, 100*deltaTime);
		s.move(0.f, 100*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//r.move(-100*deltaTime, 0.f);
		s.move(-100*deltaTime, 0.f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//r.move(100*deltaTime, 0.f);
		s.move(100*deltaTime, 0.f);
	}
}

void GameState::draw(sf::RenderWindow& window)
{
	//window.draw(r);
	window.draw(s);
}

void GameState::handleEvent(sf::Event event)
{

}

void GameState::loadContent()
{

}

void GameState::unloadContent()
{

}