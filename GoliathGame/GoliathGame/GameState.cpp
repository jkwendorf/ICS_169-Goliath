#include "GameState.h"
#include "PhysicsManager.h"

GameState::GameState(void)
	:level(new Level(1)), collisionManager(new CollisionManager())
	//:s(0, sf::Vector2i(0,0))
{
	
	//s.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));

	//r.setFillColor(sf::Color::Green);
	//r.setSize(sf::Vector2f(10, 10));
	//r.setPosition(sf::Vector2f(100, 100));

	//Code for player draw
	//p.draw(TextureManager::GetInstance().retrieveTexture("player"), 40, 23);
	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
}

GameState::~GameState(void)
{
	delete level;
	delete collisionManager;
}

void GameState::DeleteState()
{
	std::cout << "Calling GameState destructor" << std::endl;
	delete collisionManager;
	delete level;
}

void GameState::update(float deltaTime)
{
	viewCheck();

	collisionManager->setNearByTiles(level->GetCollidableTiles(p));
	p.hShot.hookedOnSomething = collisionManager->hookCollisionDetection(p.hShot);
	inputManager.update(p, collisionManager, deltaTime);

	//p.isFalling = !collisionManager->playerCollisionDetection(p);
	p.update(deltaTime);
	//p.sprite.getPosition();
}

void GameState::draw(sf::RenderWindow& window)
{
	//window.draw(r);
	level->draw(window);
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
		if(p.sprite.getPosition().x > SCREEN_WIDTH - Global::GetInstance().xOffset + Global::GetInstance().topLeft.x)
		{
			Global::GetInstance().topLeft.x = p.sprite.getPosition().x - SCREEN_WIDTH + Global::GetInstance().xOffset;
		}
	}
	else
	{
		if(p.sprite.getPosition().x < Global::GetInstance().topLeft.x + Global::GetInstance().xOffset)
		{
			Global::GetInstance().topLeft.x = p.sprite.getPosition().x - Global::GetInstance().xOffset;
		}
	}

	if(Global::GetInstance().topLeft.x < 0)
	{
		Global::GetInstance().topLeft.x = 0;
	}

	if(level->getLevelWidth() - Global::GetInstance().xOffset < p.sprite.getPosition().x)
	{
		Global::GetInstance().topLeft.x = level->getLevelWidth() - SCREEN_WIDTH;
	}


	if(p.sprite.getPosition().y - (PLAYER_DIM / 2) < 0 + Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = p.sprite.getPosition().y - (PLAYER_DIM / 2) - Global::GetInstance().yOffset;
	}

	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}