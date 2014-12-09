#include "Level.h"

Level::Level(void)
	:changeScreen(false), enemyAI(collisionManager)
{

}

Level::Level(int levelNumber)
	:changeScreen(false), levelNum(levelNumber), p(Player()), collisionManager(new CollisionManager()), inputManager(),
	maxRooms(Global::GetInstance().levelSizes.at("Level " + std::to_string(levelNum))), loading(1.0),
	enemyAI(collisionManager)
{
	
	currentRoom = new Room(levelNumber, 1, enemyList);
	background.setTexture(*TextureManager::GetInstance().retrieveTexture("banditCity"));
	background.setPosition(-75,75);
	background.scale(1.0, (float)(GAME_TILE_DIM * 22 + 100) / background.getTexture()->getSize().y);
	loadingSprite.setTexture(*TextureManager::GetInstance().retrieveTexture("loading"));
	loadingSprite.setPosition(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y);
	background.scale(1.0, (float)(GAME_TILE_DIM * 22 + 100) / background.getTexture()->getSize().y);
	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	p.resetPosition(currentRoom->getStartPos());
	//realEnemyList.push_back(new Enemy("Test",200,200, 10));

}

Level::~Level(void)
{
	DeleteLevel();
}

void Level::DeleteLevel()
{
	enemyList.clear();
	delete currentRoom;
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
		//delete currentRoom;
		enemyList.clear();
		changeScreen = true;
	}
	Global::GetInstance().topLeft.x = 0;
	Global::GetInstance().topLeft.y = 0;
	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
	//p.playerUpdate(&view, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), 0.5f);
}

void Level::update(float deltaTime)
{
	std::vector<Tile> nearTiles, nearTiles2, enemyTiles;
	currentRoom->GetGrapplableTiles(p, nearTiles2);
	if(currentRoom->NearInteractableTiles(p))
	{
		changeRoom();
	}
	if(!changeScreen)
	{
		currentRoom->GetCollidableTiles(p, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), nearTiles);

		collisionManager->setNearByTiles(nearTiles);
		collisionManager->setGrapplableTiles(nearTiles2);
	
		if(p.hShot.grappleInProgress)
		{
			if(!p.hShot.hookedOnSomething && collisionManager->hookCollisionDetection(p.hShot))
			{
				p.hShot.hookedOnSomething = true;
				Tile hookedTile = collisionManager->getHookedTile(p.hShot);
				p.hShot.grappleToLocation(sf::Vector2f(hookedTile.left + hookedTile.width/2, hookedTile.top + hookedTile.height));
			}
		}

		//if(p.hShot.hookedOnSomething)
			//std::cout << "hooked" << std::endl;
		inputManager.update(p, deltaTime);

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
			if(e->health > 0)
			{
				currentRoom->GetCollidableTiles(*e, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), enemyTiles);
				if(enemyTiles.size() > 0)
				{
					collisionManager->setNearByTiles(enemyTiles);
				}
				enemyAI.executeMovement(e.get(), p.sprite.getPosition(), deltaTime);
				e->enemyUpdate(deltaTime, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()));
				collisionManager->checkPlayerBulletToEnemies(p.ammo, e.get());
				collisionManager->checkPlayerSwordToEnemies(p.playerSword, e.get());
			}
		}
		/*
		enemyAI.executeMovement(realEnemyList.at(0), p.sprite.getPosition(), deltaTime);
		collisionManager->checkPlayerBulletToEnemies(p.ammo, realEnemyList.front());
		*/
		//check player weapon collisions
		//collisionManager
			//sword
				//collision manager will check sword hitbox with all enemies on the list
			//projectile
				//check each "moving" projectile against enemies on the screen



		//check enemy weapon collisions
	}
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
		{
			e->draw(window);
			//std::cout << e->health << std::endl;
		}
	//	enemyNum++;
	//	std::cout << "Enemy #" << enemyNum;
	}
	
	window.setView(view);
	p.drawUI(window);
}

void Level::CheckChangeScreen(BaseGameScreen*& newScreen)
{
	if(changeScreen)
	{
		newScreen = new Town();
	}
}

void Level::CleanUp()
{
}

