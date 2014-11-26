#include "GameState.h"
#include "PhysicsManager.h"

GameState::GameState(void)
	:currentRoom(new Room(1,2)), collisionManager(new CollisionManager())
	//:s(0, sf::Vector2i(0,0))
{
	
	//s.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));

	//r.setFillColor(sf::Color::Green);
	//r.setSize(sf::Vector2f(10, 10));
	//r.setPosition(sf::Vector2f(100, 100));

	//Code for player draw
	//p.draw(TextureManager::GetInstance().retrieveTexture("player"), 40, 23);
	background.setTexture(*TextureManager::GetInstance().retrieveTexture("bandit canyon level"));
	background.setPosition(0,-100);
	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	enemyList.push_back(new Enemy("Test", 1000, 700));
	p.resetPosition(currentRoom->getStartPos());
}

GameState::~GameState(void)
{
	delete currentRoom;
	delete collisionManager;
}

void GameState::DeleteState()
{
	std::cout << "Calling GameState destructor" << std::endl;
	delete collisionManager;
	delete currentRoom;
}

void GameState::update(float deltaTime)
{
	viewCheck();

	std::vector<Tile*> nearTiles, nearTiles2, enemyTiles;
	currentRoom->GetGrapplableTiles(p, nearTiles2);
	if(currentRoom->NearInteractableTiles(p))
	{
		changeRoom();
	}
	//for (int i =0; i< nearTiles2.size(); i++)
	//{
		//nearTiles2.at(i)->print();
	//}
	std::cout << p.sprite.getPosition().x << ", " << p.sprite.getPosition().y <<  std::endl;

	currentRoom->GetCollidableTiles(p, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), nearTiles);

	collisionManager->setNearByTiles(nearTiles);
	collisionManager->setGrapplableTiles(nearTiles2);
	p.hShot.hookedOnSomething = collisionManager->hookCollisionDetection(p.hShot);
	inputManager.update(p, collisionManager, deltaTime);

	//p.isFalling = !collisionManager->playerCollisionDetection(p);
	p.update(deltaTime);
	playerCheck();

	for (Enemy* e : enemyList)
	{
		currentRoom->GetCollidableTiles(*e, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), enemyTiles);
		if(enemyTiles.size() > 0)
		{
			collisionManager->setNearByTiles(enemyTiles);
		}


		e->enemyUpdate(collisionManager, deltaTime);
	}
	//p.sprite.getPosition();
}

void GameState::draw(sf::RenderWindow& window)
{
	//window.draw(r);
	window.draw(background);
	currentRoom->draw(window);
	p.draw(window);
	for(Enemy* e : enemyList)
	{
		e->draw(window);
	}
	window.setView(view);
}

void GameState::handleEvent(sf::Event event)
{

}

void GameState::loadContent()
{
	//currentRoom = new currentRoom(roomNum);
}

void GameState::unloadContent()
{
	//currentRoom* temp = currentRoom;
	//delete temp;
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

	if(currentRoom->getroomWidth() - Global::GetInstance().xOffset < p.sprite.getPosition().x)
	{
		Global::GetInstance().topLeft.x = currentRoom->getroomWidth() - SCREEN_WIDTH;
		if(currentRoom->getroomWidth() % SCREEN_WIDTH > 0)
		{
			Global::GetInstance().topLeft.x = (currentRoom->getroomWidth() / SCREEN_WIDTH) * SCREEN_WIDTH
				- SCREEN_WIDTH + (currentRoom->getroomWidth() % SCREEN_WIDTH);
		}
	}
	

	if(p.sprite.getPosition().y - (PLAYER_DIM_Y / 2) < 0 + Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = p.sprite.getPosition().y - (PLAYER_DIM_Y / 2) - Global::GetInstance().yOffset;
	}
	//Uncomment for bottom scrolling.
	else if(p.sprite.getPosition().y + (PLAYER_DIM_Y / 2) > SCREEN_HEIGHT - Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = p.sprite.getPosition().y + (PLAYER_DIM_Y / 2) + Global::GetInstance().yOffset - SCREEN_HEIGHT;
	}

	if(Global::GetInstance().topLeft.y > currentRoom->getroomHeight() - SCREEN_HEIGHT)
	{
		Global::GetInstance().topLeft.y = currentRoom->getroomHeight() - SCREEN_HEIGHT;
	}

	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void GameState::playerCheck()
{
	if(Global::GetInstance().topLeft.x == 0)
	{
		if((p.sprite.getPosition().x - (PLAYER_DIM_X / 2)) < 0)
		{
			p.sprite.setPosition((0 + PLAYER_DIM_X /2), p.sprite.getPosition().y);
		}
	}
	else if(Global::GetInstance().topLeft.x == (currentRoom->getroomWidth() - SCREEN_WIDTH))
	{
		if((p.sprite.getPosition().x + (PLAYER_DIM_X / 2)) > (currentRoom->getroomWidth() - 1))
		{
			p.sprite.setPosition((currentRoom->getroomWidth() - 1 - (PLAYER_DIM_X / 2)), p.sprite.getPosition().y);
		}

	}
}

void GameState::changeRoom()
{
	int roomNum = currentRoom->getRoomNumber();
	delete currentRoom;
	currentRoom = new Room(1, ++roomNum);
	//Move player to the start pos in new room
	p.resetPosition(currentRoom->getStartPos());
}