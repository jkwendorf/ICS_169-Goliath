#include "GameState.h"

GameState::GameState(void)
{
	r.setFillColor(sf::Color::Green);
	r.setSize(sf::Vector2f(10, 10));
	r.setPosition(sf::Vector2f(100, 100));
}

GameState::~GameState(void)
{
}

void GameState::update(float deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		r.move(0.f, -100*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		r.move(0.f, 100*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		r.move(-100*deltaTime, 0.f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		r.move(100*deltaTime, 0.f);
	}
}

void GameState::draw(sf::RenderWindow& window)
{
	window.draw(r);
}

void GameState::loadContent()
{

}

void GameState::unloadContent()
{

}