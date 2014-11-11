#include "GameState.h"

GameState::GameState(void)
	:s(1)
	//:s(0, sf::Vector2i(0,0))
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
	
	collisionManager.setNearByTiles(s.GetNearTiles(p.sprite.getPosition()));
	p.isFalling = !collisionManager.playerCollisionDetection(p);
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
	if(p.facingRight)
	{

		if(p.sprite.getPosition().x > Global::GetInstance().x - Global::GetInstance().xOffset + topLeft.x)
		{
			topLeft.x = p.sprite.getPosition().x - Global::GetInstance().x + Global::GetInstance().xOffset;
		}
	}
	else
	{
		if(p.sprite.getPosition().x < topLeft.x + Global::GetInstance().xOffset)
		{
			topLeft.x = p.sprite.getPosition().x - Global::GetInstance().xOffset;
		}
	}

	if(topLeft.x < 0)
	{
		topLeft.x = 0;
	}

	//ND: Vertical will be implemented once I have a test file for that

	view.reset(sf::FloatRect(topLeft.x, topLeft.y, (float) Global::GetInstance().x, (float) Global::GetInstance().y));
}