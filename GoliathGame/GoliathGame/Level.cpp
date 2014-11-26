#include "Level.h"

Level::Level(void)
{

}

Level::Level(int levelNumber)
	:levelNum(levelNumber), currentRoom(new Room(levelNumber, 1)), p(Player()), collisionManager(new CollisionManager()), inputManager(new InputManager())
{
	background.setTexture(*TextureManager::GetInstance().retrieveTexture("bandit canyon level"));
	background.setPosition(0,-100);
	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	p.resetPosition(currentRoom->getStartPos());
}

Level::~Level(void)
{
	delete currentRoom;
	delete inputManager;
	delete collisionManager;
}

void Level::viewCheck()
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

void Level::playerCheck()
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

void Level::changeRoom()
{
	int roomNum = currentRoom->getRoomNumber();
	delete currentRoom;
	currentRoom = new Room(levelNum, ++roomNum);
	//Move player to the start pos in new room
	p.resetPosition(currentRoom->getStartPos());
}

void Level::update(float deltaTime)
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
	inputManager->update(p, collisionManager, deltaTime);

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
}

void Level::draw(sf::RenderWindow& window)
{
	//window.draw(r);
	window.draw(background);
	currentRoom->draw(window);
	p.draw(window);
	window.setView(view);
}

