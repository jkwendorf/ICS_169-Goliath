#include "Level.h"
#include "GrapplingState.h"

Level::Level(void)
	:changeScreen(false), enemyAI(collisionManager)
{

}

Level::Level(int levelNumber, int roomNumber)
	:changeScreen(false), levelNum(levelNumber), p(), collisionManager(new CollisionManager()), inputManager(),
	maxRooms(Global::GetInstance().levelSizes.at("Level " + std::to_string(levelNum))), loading(1.0),
	enemyAI(collisionManager)
{
	p.init(collisionManager, new JumpingState());
	currentRoom = new Room(levelNumber, roomNumber, enemyList, arrowTileList, destructTileList);
	background.setTexture(*TextureManager::GetInstance().retrieveTexture("bandit canyon level"));
	sf::Color color = background.getColor();
	background.setColor(sf::Color(color.r, color.g, color.b, 200));
	background.setPosition(-75,75);
	background.scale(1.0, (float)(GAME_TILE_DIM * 22 + 100) / background.getTexture()->getSize().y);
	loadingSprite.setTexture(*TextureManager::GetInstance().retrieveTexture("loading"));
	loadingSprite.setPosition(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y);
	background.scale(1.0, (float)(GAME_TILE_DIM * 22 + 100) / background.getTexture()->getSize().y);
	Global::GetInstance().topLeft.x = 0;
	Global::GetInstance().topLeft.y = 0;
	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	p.resetPosition(currentRoom->getStartPos());
	setArrowTileArrows();
	//realEnemyList.push_back(new Enemy("Test",200,200, 10));

}

Level::~Level(void)
{
	DeleteLevel();
}

void Level::DeleteLevel()
{
	enemyList.clear();
	arrowTileList.clear();
	arrows.clear();
	destructTileList.clear();
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
		arrowTileList.clear();
		arrows.clear();
		destructTileList.clear();
		currentRoom = new Room(levelNum, ++roomNum, enemyList, arrowTileList, destructTileList);
		setArrowTileArrows();
		//Move player to the start pos in new room
		p.resetPosition(currentRoom->getStartPos());
		p.init(collisionManager, new JumpingState());
	}
	else
	{
		//delete currentRoom;
		enemyList.clear();
		arrowTileList.clear();
		arrows.clear();
		destructTileList.clear();
		changeScreen = true;
		
	}
	Global::GetInstance().topLeft.x = 0;
	Global::GetInstance().topLeft.y = 0;
	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
	p.isFalling = true;

	//p.playerUpdate(&view, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), 0.5f);
}

void Level::update(float deltaTime)
{
	if((p.sprite.getPosition().y + PLAYER_DIM_Y/2) >= currentRoom->getroomHeight())
	{
		p.resetPosition(currentRoom->getStartPos() + sf::Vector2f(50, -10));
	}

	std::vector<Tile*> nearTiles, nearTiles2, enemyTiles;
	currentRoom->GetGrapplableTiles(p, nearTiles2);
	int nearTile = currentRoom->NearInteractableTiles(p);
	if( nearTile != -999)
	{
		if(nearTile == 18 || nearTile == 19)
			changeRoom();
		else if (nearTile == 20)
		{
			p.takeDamage();
		}
			
	}
	if(!changeScreen)
	{

		currentRoom->GetCollidableTiles(p, sf::Vector2f(PLAYER_DIM_X, PLAYER_DIM_Y), nearTiles);

		collisionManager->setNearByTiles(nearTiles);
		collisionManager->setGrapplableTiles(nearTiles2);
	
		if(p.hShot.grappleInProgress)
		{
			p.hShot.hitNonGrappleTile = collisionManager->hShotHitNonGrappleTile(p.hShot);
			if(!p.hShot.hookedOnSomething && collisionManager->hookCollisionDetection(p.hShot))
			{
				p.hShot.hookedOnSomething = true;
				Tile* hookedTile = collisionManager->getHookedTile(p.hShot);
				
				/*if(hookedTile->getTileNum() == 6)
				{
					p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left + hookedTile->width + p.sprite.getGlobalBounds().width/2, hookedTile->top + hookedTile->height/2));
					p.shouldHang = true;
				}
				else if(hookedTile->getTileNum() == 7)
				{
					p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left - p.sprite.getGlobalBounds().width/2, hookedTile->top + hookedTile->height/2));
					p.shouldHang = true;
				}*/
				if(hookedTile->getTileNum() == 6)
					p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left - hookedTile->width/2, hookedTile->top - hookedTile->height/2 - 28));
				else if(hookedTile->getTileNum() == 7)
					p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left + hookedTile->width/2 + GAME_TILE_DIM - 5, hookedTile->top - hookedTile->height/2 - 28));
				else
					p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left + hookedTile->width/2, hookedTile->top + 5));

				//p.newState = new GrapplingState();
				delete p.currentState;
				p.currentState = new GrapplingState();
			}
		}

		//if(p.hShot.hookedOnSomething)
			//std::cout << "hooked" << std::endl;


		//p.isFalling = !collisionManager->playerCollisionDetection(p);
		//p.update(deltaTime);
		p.playerUpdate(&view, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), deltaTime);

		inputManager.update(p, &view, deltaTime);
		p.handleInput();
		//Check to see if the player has died
		if(p.checkDead())
		{
			p.resetPosition(currentRoom->getStartPos());
			p.resetHealth();
		}

		/*if((!p.hShot.hookedOnSomething || !p.hShot.grappleInProgress) && !p.isHanging && !p.isVaulting)
		{
			collisionManager->checkTreasure(&p);
			//std::cout << "Check Collision" << std::endl;
			if(p.isFalling)
			{
				//std::cout << "Falling Collision" << std::endl;
				/*while(collisionManager->playerCollisionDetection(&p))
				{
					if((collisionManager->getCollidedTile(p) != nullptr) && 
						((collisionManager->getCollidedTile(p)->getFlags() & TILE::HAZARDMASK) != 0))
					{
						p.takeDamage();
					}
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
				if(p.hShot.isDisabled)
					p.hShot.isDisabled = false;
				if((collisionManager->getCollidedTile(p) != nullptr) && 
					((collisionManager->getCollidedTile(p)->getFlags() & TILE::HAZARDMASK) != 0))
				{
					p.takeDamage();
				}
				//std::cout << "Ground Collision" << std::endl;
				if(collisionManager->wallBlockingCharacter(&p))
				{
					
					p.move(moveOutOfTileHorizontally(p, collisionManager->getCollidedTile(p)));	
					
				}
			}
		}*/

		for(Projectile& po : p.ammo)
		{
			std::vector<Tile*> proTile;
			if(po.moving)
			{
				std::cout << "Projectile position: " << po.sprite.getPosition().x << " " << po.sprite.getPosition().y << std::endl;	
				currentRoom->GetCollidableTiles(po, sf::Vector2f(po.sprite.getTexture()->getSize().x/10,
					po.sprite.getTexture()->getSize().y/10), proTile);
				for(auto& t : proTile)
				{
					std::cout << t->getTileNum() << std::endl;
				}
				if(proTile.size() > 0)
				{
					collisionManager->setNearByTiles(proTile);
				}

				if(collisionManager->playerCollisionDetection(&po))
				{
					po.moving = false;
					po.startTime = 0;
				}

				for(auto& e : enemyList)
					collisionManager->checkPlayerBulletToEnemies(po, e.get());		
			}
		}

		for (auto& e : enemyList)
		{
			if(e->health > 0)
			{
				std::vector<Tile*> proTile;
				currentRoom->GetCollidableTiles(*e, sf::Vector2f(PLAYER_DIM_X, PLAYER_DIM_Y), enemyTiles);

				if(enemyTiles.size() > 0)
				{
					collisionManager->setNearByTiles(enemyTiles);
				}
					
				for(auto& ne : enemyList)
				{
					if(e.get() != ne.get() 
						&& e.get()->sprite.getGlobalBounds().intersects(ne.get()->sprite.getGlobalBounds()))
					{
						std::cout << "Enemy is hitting each other" << std::endl;
						enemyAI.moveOutOfOtherEnemy(e.get(), ne.get(), deltaTime);
					}
				}

				enemyAI.executeMovement(e.get(), p.sprite.getPosition(), deltaTime);

				e->enemyUpdate(deltaTime, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()));

				for(Projectile& po : e.get()->ammo)
				{
					if(po.moving)
					{
						currentRoom->GetCollidableTiles(po, sf::Vector2f(po.sprite.getTexture()->getSize().x/10,
							po.sprite.getTexture()->getSize().y/10), proTile);

						if(proTile.size() > 0)
						{
							collisionManager->setNearByTiles(proTile);
						}

						if(collisionManager->playerCollisionDetection(&po))
						{
							po.moving = false;
						}

						collisionManager->checkEnemyBulletToPlayer(po, &p);
					}
				}

				//ISILDOR LOOK HERE FOR RAYCAST CODE
				Projectile& ray = e.get()->raycast;

				if(ray.moving)
				{
					currentRoom->GetCollidableTiles(ray, sf::Vector2f(ray.sprite.getTexture()->getSize().x/10,
							ray.sprite.getTexture()->getSize().y/10), proTile);

						if(proTile.size() > 0)
						{
							collisionManager->setNearByTiles(proTile);
						}
						//std::cout << "Enemy " << i << " ray position: " << ray.sprite.getPosition().x << std::endl;
						//std::cout << "Enemy " << i << " position: " << e.get()->sprite.getPosition().x << std::endl;
						if(collisionManager->playerCollisionDetection(&ray))
						{
							e.get()->foundPlayer = false;
							e.get()->resetRay();
						}
						else if(collisionManager->checkIfEnemyInRange(ray, &p))
						{
							e.get()->resetRay();
							e.get()->foundPlayer = true;
						}
				}
			}
		}

		for(auto& e : enemyList)
		{
			collisionManager->checkPlayerSwordToEnemies(p.playerSword, e.get());
			collisionManager->checkEnemySwordToPlayer(e.get()->eSword, &p);
		}

		int i = 0;
		//std::cout << "Player position:" << p.sprite.getPosition().x << " " << p.sprite.getPosition().y << std::endl;
		checkDestructableTiles();

		for(auto& a : arrows)
		{
			i++;
			std::vector<Tile*> proTile;
			a->update(deltaTime);
			//std::cout << "ARROW " << i << " position:" << a->sprite.getPosition().x << " " << a->sprite.getPosition().y << std::endl;	
			if(a->moving)
			{
				currentRoom->GetCollidableTiles(*a, sf::Vector2f(a->sprite.getTexture()->getSize().x/10,
					a->sprite.getTexture()->getSize().y/10), proTile);

				if(proTile.size() > 0)
				{
					collisionManager->setNearByTiles(proTile);
				}

				if(collisionManager->playerCollisionDetection(a))
				{
					a->moving = false;
					a->setLocation(a->startLocation);
				}

				if(collisionManager->checkIfEnemyInRange(*a, &p))
				{
					p.health -= a->damage;
					a->moving = false;
					a->setLocation(a->startLocation);
					std::cout << "ARROW " << i << " hit player" << std::endl;
				}
			}
			else 
			{
				a->setLocation(a->startLocation);
				a->moving = true;
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

	//window.draw(Global::GetInstance().testingRect);

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
	
	for (auto& a : arrows)
	{
		if(a->moving)
		{
			a->draw(window);
		}
	}

	window.setView(view);
	p.drawUI(window);
}

bool Level::CheckChangeScreen()
{
	return changeScreen;
}

void Level::CleanUp()
{
}

// Creates arrows based off positions of arrow shooter tiles
void Level::setArrowTileArrows()
{
	for(auto& a : arrowTileList)
	{
		if(a->getDirection().x == 1.0)
		{
			Projectile* pro = new Projectile(sf::Vector2f(a->left + (GAME_TILE_DIM), a->top), a->getDirection());
			pro->damage = 25;
			arrows.push_back(pro);
		}
		else if(a->getDirection().x == -1.0)
		{
			Projectile* pro = new Projectile(sf::Vector2f(a->left - (GAME_TILE_DIM), a->top), a->getDirection());
			pro->damage = 25;
			arrows.push_back(pro);
		}
		else if(a->getDirection().y == 1.0)
		{
			Projectile* pro = new Projectile(sf::Vector2f(a->left, a->top + (GAME_TILE_DIM)), a->getDirection());
			pro->damage = 25;
			arrows.push_back(pro); 
		}
		else if(a->getDirection().y == -1.0)
		{
			Projectile* pro = new Projectile(sf::Vector2f(a->left, a->top - (GAME_TILE_DIM)), a->getDirection());
			pro->damage = 25;
			arrows.push_back(pro);
		}

	}
}

// Goes through each destructable tile within the level and checks to see if we should destroy them
void Level::checkDestructableTiles()
{
	for (auto it = destructTileList.begin(); it != destructTileList.end();)
	{
		if(collisionManager->playerSwordCollideWithTile(p.playerSword, *it))
		{
			auto itToErase = it;
			it++;
			delete (*itToErase);
			*itToErase = new Tile();
			destructTileList.erase(itToErase);
			continue;
		}
		it++;
	}
}