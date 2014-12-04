#include "Level.h"

Level::Level(void)
	:changeScreen(false)
{

}

Level::Level(int levelNumber)
	:changeScreen(false), levelNum(levelNumber), p(Player()), collisionManager(new CollisionManager()), inputManager(new InputManager()),
	maxRooms(Global::GetInstance().levelSizes.at("Level " + std::to_string(levelNum))), loading(1.0),
	enemyAI(new EnemyAI(collisionManager))
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

	std::cout << "Room Width: " << currentRoom->getroomWidth() << std::endl;
	//enemyList.push_back(new Enemy("Test", 1000, 1000));
	//enemyList.push_back(new Enemy("Test", 700, 400));
}

Level::~Level(void)
{
	//std::cout << "Deleting the level" << std::endl;
	delete currentRoom;
	delete inputManager;
	delete collisionManager;
	delete enemyAI;
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
		//changeScreen = true;
	}
	Global::GetInstance().topLeft.x = 0;
	Global::GetInstance().topLeft.y = 0;
	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
	std::cout << Global::GetInstance().topLeft.x << std::endl;
}

void Level::update(float deltaTime)
{
	std::vector<Tile*> nearTiles, nearTiles2, enemyTiles;
	currentRoom->GetGrapplableTiles(p, nearTiles2);
	if(currentRoom->NearInteractableTiles(p))
	{
		changeRoom();
	}
//	std::cout << "Player Position: " << p.sprite.getPosition().x  << std::endl;

	currentRoom->GetCollidableTiles(p, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), nearTiles);

	collisionManager->setNearByTiles(nearTiles);
	collisionManager->setGrapplableTiles(nearTiles2);
	
	if(p.hShot.grappleInProgress)
	{
		if(!p.hShot.hookedOnSomething && collisionManager->hookCollisionDetection(p.hShot))
		{
			p.hShot.hookedOnSomething = true;
			Tile* hookedTile = collisionManager->getHookedTile(p.hShot);
			p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left + hookedTile->width/2, hookedTile->top + hookedTile->height));
		}
	}

	//if(p.hShot.hookedOnSomething)
		//std::cout << "hooked" << std::endl;
	inputManager->update(p, collisionManager, deltaTime);

	//p.isFalling = !collisionManager->playerCollisionDetection(p);
	//p.update(deltaTime);
	p.playerUpdate(&view, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), deltaTime);

	if(!p.hShot.hookedOnSomething || !p.hShot.grappleInProgress)
	{
		//std::cout << "Check Collision" << std::endl;
		if(p.isFalling)
		{
			//std::cout << "Falling Collision" << std::endl;
			while(collisionManager->playerCollisionDetection(&p))
			{
				p.moveOutOfTile(collisionManager->getCollidedTile(p));
			}
		}
		else if(!collisionManager->tileBelowCharacter(&p))
		{
			//std::cout << "Start Falling" << std::endl;
			p.isFalling = true;
		}
		else if(collisionManager->tileBelowCharacter(&p))
		{
			//std::cout << "Ground Collision" << std::endl;
			if(collisionManager->wallBlockingCharacter(&p))
			{
				p.move(moveOutOfTileHorizontally(p, collisionManager->getCollidedTile(p)));
			}
		}
	}
	for (auto& e : enemyList)
	{
		currentRoom->GetCollidableTiles(*e, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), enemyTiles);
		if(enemyTiles.size() > 0)
		{
			collisionManager->setNearByTiles(enemyTiles);
		}
		enemyAI->executeMovement(&*e, p.sprite.getPosition(), deltaTime);
		e->enemyUpdate(deltaTime, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()));
	}

	//collisionManager->checkPlayerBulletToEnemies(p.ammo, enemyList);
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
	//check player weapon collisions
	//collisionManager
		//sword
			//collision manager will check sword hitbox with all enemies on the list
		//projectile
			//check each "moving" projectile against enemies on the screen



	//check enemy weapon collisions
}

void Level::draw(sf::RenderWindow& window)
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
		if(e->health > 0)
			e->draw(window);
	//	enemyNum++;
	//	std::cout << "Enemy #" << enemyNum;
	}
	window.setView(view);
}

bool Level::CheckChangeScreen()
{
	return changeScreen;
}

void Level::CleanUp()
{
}

