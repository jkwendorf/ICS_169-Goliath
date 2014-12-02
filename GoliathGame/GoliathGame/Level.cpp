#include "Level.h"

Level::Level(void)
{

}

Level::Level(int levelNumber)
	:levelNum(levelNumber), p(Player()), collisionManager(new CollisionManager()), inputManager(new InputManager()), 
	maxRooms(Global::GetInstance().levelSizes.at("Level " + std::to_string(levelNum))), loading(1.0)
{
	currentRoom = new Room(levelNumber, 1, enemyList);
	background.setTexture(*TextureManager::GetInstance().retrieveTexture("bandit canyon level"));
	background.setPosition(0,-100);
	background.scale(1.0, (float)(GAME_TILE_DIM * 22 + 100) / background.getTexture()->getSize().y);
	loadingSprite.setTexture(*TextureManager::GetInstance().retrieveTexture("loading"));
	loadingSprite.setPosition(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y);
	background.scale(1.0, (float)(GAME_TILE_DIM * 22 + 100) / background.getTexture()->getSize().y);
	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	p.resetPosition(currentRoom->getStartPos());
}

Level::~Level(void)
{
	//std::cout << "Deleting the level" << std::endl;
	delete currentRoom;
	delete inputManager;
	delete collisionManager;
}

void Level::DeleteLevel()
{
	std::cout << "Deleting the level" << std::endl;
	delete currentRoom;
	delete inputManager;
	delete collisionManager;
}

void Level::changeRoom()
{
	loading = 1.0;
	int roomNum = currentRoom->getRoomNumber();
	if (roomNum < maxRooms)
	{
		delete currentRoom;
		enemyList.clear();
		currentRoom = new Room(levelNum, ++roomNum, enemyList);
		//Move player to the start pos in new room
		p.resetPosition(currentRoom->getStartPos());
	}
	else
	{
		delete currentRoom;
		enemyList.clear();
		currentRoom = new Room(levelNum, 1, enemyList);
		//Move player to the start pos in new room
		p.resetPosition(currentRoom->getStartPos());
	}
	Global::GetInstance().topLeft.x = 0;
	Global::GetInstance().topLeft.y = 0;
	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void Level::update(float deltaTime)
{
	if(loading < 0)
	{
		std::vector<Tile*> nearTiles, nearTiles2, enemyTiles;
		currentRoom->GetGrapplableTiles(p, nearTiles2);
		if(currentRoom->NearInteractableTiles(p))
		{
			changeRoom();
		}

		currentRoom->GetCollidableTiles(p, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), nearTiles);

		collisionManager->setNearByTiles(nearTiles);
		collisionManager->setGrapplableTiles(nearTiles2);
		p.hShot.hookedOnSomething = collisionManager->hookCollisionDetection(p.hShot);
		inputManager->update(p, collisionManager, deltaTime);

		//p.isFalling = !collisionManager->playerCollisionDetection(p);
		//p.update(deltaTime);
		p.playerUpdate(&view, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), deltaTime);

		for (auto& e : enemyList)
		{
			currentRoom->GetCollidableTiles(*e, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), enemyTiles);
			if(enemyTiles.size() > 0)
			{
				collisionManager->setNearByTiles(enemyTiles);
			}
			e->enemyUpdate(collisionManager, deltaTime, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), p.sprite.getPosition());
		}
		for(Tile* t : nearTiles)
		{
			delete t;
		}
		for(Tile* t : nearTiles2)
		{
			delete t;
		}
		for(Tile* t : enemyTiles)
		{
			delete t;
		}
	}
	else
	{

		loading -= deltaTime;
	}
}

void Level::draw(sf::RenderWindow& window)
{
	if(loading < 0)
	{
		//window.draw(r);
		window.draw(background);
		currentRoom->draw(window);
		p.draw(window);
		//UNCOMMENT FOR TESTING
		//ALSO, UNCOMMENT CODE IN Enemy.update TO FINISH TEST OUTPUT
		//int enemyNum = 0;
		for(auto& e : enemyList)
		{
			e->draw(window);
		//	enemyNum++;
		//	std::cout << "Enemy #" << enemyNum;
		}
		window.setView(view);
	}
	else
	{
		//std::cout << view.getCenter().x << "," << view.getCenter().y << std::endl;
		loadingSprite.setPosition(view.getCenter().x, view.getCenter().y);
		window.draw(loadingSprite);
	}
}

void Level::CleanUp()
{
}

