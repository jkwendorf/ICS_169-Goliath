#include "GameState.h"

GameState::GameState(void)
	:s("LongLevel", sf::Vector2i(0,0))
{
	//s.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));

	//r.setFillColor(sf::Color::Green);
	//r.setSize(sf::Vector2f(10, 10));
	//r.setPosition(sf::Vector2f(100, 100));

	//Code for player draw
	//p.draw(TextureManager::GetInstance().retrieveTexture("player"), 40, 23);
	view.reset(sf::FloatRect(0, 0, (float) Global::GetInstance().x, (float) Global::GetInstance().y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
}

GameState::~GameState(void)
{
}

void GameState::update(float deltaTime)
{
	//Update for Player still needs to be fleshed out
	//p.update();

	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
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
	}*/

	viewCheck();
	inputManager.update(p, deltaTime);
	p.update(deltaTime);
	//p.sprite.getPosition();
}

void GameState::draw(sf::RenderWindow& window)
{
	//window.draw(r);
	s.draw(window);
	p.draw(window);
	window.setView(view);
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

void GameState::viewCheck()
{
	playerPos.x = p.sprite.getPosition().x + 100 - (Global::GetInstance().x / 2);
	playerPos.y = p.sprite.getPosition().y + 100 - (Global::GetInstance().y / 2);

	if(playerPos.x < 0)
	{
		playerPos.x = 0;
	}
	if(playerPos.y < 0)
	{
		playerPos.y = 0;
	}

	view.reset(sf::FloatRect(playerPos.x, playerPos.y, (float) Global::GetInstance().x, (float) Global::GetInstance().y));
}