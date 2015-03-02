#include "Level.h"
#include "GrapplingState.h"
#include "StateManager.h"
#include "LoadingState.h"
#include "AudioManager.h"

Level::Level(void)
	:changeScreen(false), enemyAI(collisionManager)
{

}

Level::Level(int levelNumber, int roomNumber)
	:changeScreen(false), levelNum(levelNumber), p(), collisionManager(new CollisionManager()), inputManager(),
	levelInfo(Global::GetInstance().levelInfo.at("Level " + std::to_string(levelNum))), loading(1.0),
	enemyAI(collisionManager), arrowCool(2.0f), screenShakeDuration(.65f), screenShakeCooldown(10.0f), currentScreenShakeCooldown(0.0f),
	arrowsCanFire(true), fixedTime(0.0f), levelStart(true), screenShake(false), shakeOffset(1), introTimer(5.0f)
{
	
	currentRoom = new Room(levelNumber, roomNumber, enemyList, arrowTileList, destructTileList, hitPointTileList);
	p.init(collisionManager, new JumpingState(), currentRoom->numTreasures);
	//background.setTexture(*TextureManager::GetInstance().retrieveTexture("bandit canyon level"));
	//sf::Color color = background.getColor();
	//background.setColor(sf::Color(color.r, color.g, color.b, 200));
	//background.setPosition(-75,75);
	//background.scale(1.0, (float)(GAME_TILE_DIM * 22 + 100) / background.getTexture()->getSize().y);
	loadingSprite.setTexture(*TextureManager::GetInstance().retrieveTexture("loading"));
	loadingSprite.setPosition(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y);
	Global::GetInstance().topLeft.x = 0;
	Global::GetInstance().topLeft.y = 0;
	camera.setRoomSize(sf::Vector2f(currentRoom->getroomWidth(), currentRoom->getroomHeight()));
	camera.viewReset();
	p.resetPosition(currentRoom->getStartPos());
	setArrowTileArrows();
	//realEnemyList.push_back(new Enemy("Test",200,200, 10));
	particle = Particle("rock", sf::Vector2f(50, 100), sf::Vector2f(0, 1), 5, 250);
	particleEmitter = ParticleEmitter("RockParticle2", sf::Vector2f(0, -400), sf::Vector2f(0, 1), 10, 350, 10, "debris");
	coneEmitter = ParticleEmitter("RockParticle1", sf::Vector2f(100, 1200), sf::Vector2f(.5, .5), 1, 50, 30, "cone");
	loadSounds();
	//shakeScreen(5.0, 100);

	introDescription = sf::Text(levelInfo.description, Global::GetInstance().font);
	introDescription.setOrigin(introDescription.getGlobalBounds().width/2, introDescription.getGlobalBounds().height/2);
	if (levelInfo.imageName != "")
	{
		description = sf::Sprite(*TextureManager::GetInstance().retrieveTexture(levelInfo.imageName));
		description.setOrigin(description.getGlobalBounds().width/2, description.getGlobalBounds().height/2);
		description.setPosition(Global::GetInstance().topLeft.x + SCREEN_WIDTH/2, Global::GetInstance().topLeft.y + SCREEN_HEIGHT/2);
	}
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
	hitPointTileList.clear();
	delete currentRoom;
	delete collisionManager;
	//particleEmitter.~ParticleEmitter();
}

void Level::changeRoom()
{
	loading = 1.0;
	int roomNum = currentRoom->getRoomNumber();
	if (roomNum < levelInfo.levelSize)
	{
		delete currentRoom;
		enemyList.clear();
		arrowTileList.clear();
		arrows.clear();
		destructTileList.clear();
		hitPointTileList.clear();
		currentRoom = new Room(levelNum, ++roomNum, enemyList, arrowTileList, destructTileList, hitPointTileList);

		setArrowTileArrows();
		//Move player to the start pos in new room
		p.resetPosition(currentRoom->getStartPos());
		p.init(collisionManager, new JumpingState(), currentRoom->numTreasures);
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
	camera.setRoomSize(sf::Vector2f(currentRoom->getroomWidth(), currentRoom->getroomHeight()));
	camera.viewReset();
	p.isFalling = true;
	p.vel.x = 0;
	p.vel.y = 0;
	StateManager::getInstance().addState(TRANSITION, new LoadingState(), true);

	//p.playerUpdate(&view, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), 0.5f);
}

void Level::update(float deltaTime)
{
	
	particleEmitter.update(deltaTime);
	//coneEmitter.update(deltaTime);
	particle.update(deltaTime);
	currentScreenShakeCooldown += deltaTime;
	camera.viewChange(p.sprite.getPosition());
	currentRoom->update(deltaTime);
	if (currentRoom->bg.hitFloor()) {
		goliathSound[STOMP1].play();
		shakeScreen(1.0f, 20);
		currentRoom->bg.setHitFloor(false);
		particleEmitter.resetAllParticles();
		
	}

	//SCREENSHAKE CODE
	if(screenShake)
	{
		if(currentScreenShakeCooldown <= screenShakeDuration)
		{
			//std::cout << "ScreenShake should occur" << std::endl;
			//currentRoom->bg.setScale(0, 0.0f, 1.0f);
			viewChangeOffset.x = rand() % shakeOffset;
			viewChangeOffset.y = rand() % shakeOffset;
			camera.shakeScreen(viewChangeOffset.x, viewChangeOffset.y);
			
			//view.move(viewChangeOffset);
			p.updateUI(viewChangeOffset);
			Global::GetInstance().ControllerVibrate(75, 75);
		}
		else if(currentScreenShakeCooldown > screenShakeDuration)
		{
			//std::cout << "Should be normal view" << std::endl;
			//currentRoom->bg.setScale(0, 0.0f, -1.0f);
			screenShake = false;
			Global::GetInstance().ControllerVibrate();
		}
	}
	else
	{
		camera.viewReset();
		p.updateUI();
	}
	

	if((p.sprite.getPosition().y + PLAYER_DIM_Y/2) >= currentRoom->getroomHeight())
	{
		p.resetPosition(currentRoom->getStartPos() + sf::Vector2f(50, -10));
		/*if(!levelStart)
		{
			p.resetHealth();
		}
		if(levelStart)
		{
			levelStart = false;
			p.resetHealth();
		}*/
		p.resetHealth();

	}

	std::vector<Tile*> nearTiles, nearTiles2, enemyTiles;
	currentRoom->GetGrapplableTiles(p, nearTiles2);
	int nearTile = currentRoom->NearInteractableTiles(p);
	if( nearTile != -999)
	{
		if((nearTile == 18 || nearTile == 19) && hitPointTileList.empty())
		{
			changeRoom();
			deltaTime = 0.f;
			StateManager::getInstance().setTimeReset(true);
		}
		else if (nearTile == 20)
		{
			p.takeDamage();
		}
		
	}
	if(!changeScreen)
	{

		currentRoom->GetCollidableTiles(p, nearTiles, true);

		collisionManager->setNearByTiles(nearTiles);
		if(!p.hShot.grappleInProgress)
			collisionManager->setGrapplableTiles(nearTiles2);

		collisionManager->checkTreasure(p);
		
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
				else if(hookedTile->getTileNum() == 26)
				{
					// Hookshot goliath hitpoint
					p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left + hookedTile->width/2, hookedTile->top + hookedTile->height));
					p.destroyGoliathHitpoint = true;
					p.goliathHitpoint = hookedTile;
				}
				else
					//p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left + hookedTile->width/2, hookedTile->top + 5));
					p.hShot.grappleToLocation(sf::Vector2f(hookedTile->left + hookedTile->width/2, hookedTile->top + hookedTile->height));

				//p.newState = new GrapplingState();
				delete p.currentState;
				p.currentState = new GrapplingState();
			}
		}

		//if(p.hShot.hookedOnSomething)
			//std::cout << "hooked" << std::endl;


		//p.isFalling = !collisionManager->playerCollisionDetection(p);
		//p.update(deltaTime);
		p.playerUpdate(sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), deltaTime);


		inputManager.update(p, &camera, deltaTime);
		p.handleInput();
		//Check to see if the player has died
		if(p.checkDead())
		{
			p.resetPosition(currentRoom->getStartPos());
			p.resetHealth();
			delete p.currentState;
			p.currentState = new JumpingState();
			//currentRoom->bg.reset();
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

	fixedTime += deltaTime;
	if(fixedTime >= 50.0f)
	{
		fixedTime -= 50.0f;

		for(Projectile& po : p.ammo)
		{
			std::vector<Tile*> proTile;
			if(po.moving)
			{
				std::cout << "Projectile position: " << po.sprite.getPosition().x << " " << po.sprite.getPosition().y << std::endl;	
				currentRoom->GetCollidableTiles(po, proTile);
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
				currentRoom->GetCollidableTiles(*e, enemyTiles);

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
						currentRoom->GetCollidableTiles(po, proTile);

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
					currentRoom->GetCollidableTiles(ray, proTile);

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
}

		int i = 0;
		//std::cout << "Player position:" << p.sprite.getPosition().x << " " << p.sprite.getPosition().y << std::endl;
		checkHitPointTilesForDmg(deltaTime);
		checkDestructableTiles();

		//CODE TO DISABLE ARROW SHOOTER
		//NEEDS TO BE REPLACED WITH SWITCH POSITION
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
		{
			arrowsCanFire = !arrowsCanFire;
			if(arrowsCanFire == true)
			{
				arrowCool = 2.1f;
			}
		}

		arrowCool += deltaTime;

		for(auto& a : arrows)
		{
			i++;
			std::vector<Tile*> proTile;
			a->update(deltaTime);

			if(a->moving)
			{
				currentRoom->GetCollidableTiles(*a, proTile);

				if(proTile.size() > 0)
				{
					collisionManager->setNearByTiles(proTile);
				}

				if(collisionManager->playerCollisionDetection(a))
				{
					a->moving = false;
					a->startTime = 0.0f;
				}

				if(collisionManager->checkIfEnemyInRange(*a, &p))
				{
					if(!p.gotHit)
					{
						p.health -= a->damage;
						if(p.health > 0)
						{
							p.playHurtSound();
						}
						p.gotHit = true;

						a->moving = false;
						a->setLocation(a->startLocation);
						a->drawPlease = false;
						a->startTime = 0.0f;
					}

				}
			}
			else if(arrowCool > 2.0f && arrowsCanFire)
			{
				a->setLocation(a->startLocation);
				a->drawPlease = true;
				a->moving = true;
			}
		}

		if(arrowCool > 2.0f)
		{
			arrowCool = 0.0f;
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
		//std::cout << "View level: " << view.getCenter().x - view.getSize().x/2 << std::endl;
		currentRoom->setViewPosition(view.getCenter().x - view.getSize().x/2);
	}

	if(introTimer > 0 && currentRoom->getRoomNumber() == 1)
	{
		introTimer -= deltaTime;
		//introDescription.setScale(introDescription.getScale().x - 0.05, introDescription.getScale().y - 0.05);
		introDescription.setPosition(Global::GetInstance().topLeft.x + SCREEN_WIDTH/2, Global::GetInstance().topLeft.y + SCREEN_HEIGHT/2);
		if (levelInfo.imageName != "")
		{
			description.setPosition(Global::GetInstance().topLeft.x + SCREEN_WIDTH/2, Global::GetInstance().topLeft.y + SCREEN_HEIGHT/2);
			description.setColor(sf::Color(description.getColor().r, description.getColor().g, description.getColor().b, description.getColor().a - 0.01));
		}
	}
}

void Level::draw(sf::RenderWindow& window)
{
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
		a->draw(window);
	}
	particle.draw(window);
	particleEmitter.draw(window);
	//coneEmitter.draw(window);
	window.setView(camera.getView());
	p.drawUI(window);
	if( introTimer > 0 && currentRoom->getRoomNumber() == 1)
	{
		window.draw(introDescription);
		if (levelInfo.imageName != "")
		{
			window.draw(description);
		}
	}
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
		//std::cout << "Shooter: " << a->left << ", " << a->top << std::endl;
		if(a->getDirection().x == 1.0)
		{
			Projectile* pro = new Projectile(sf::Vector2f(a->left + (GAME_TILE_DIM), a->top), a->getDirection());
			pro->drawPlease = false;
			pro->damage = 25;
			arrows.push_back(pro);
			//std::cout << pro->hitbox.getGlobalBounds().left << ", " << pro->hitbox.getGlobalBounds().top << std::endl;
		}
		else if(a->getDirection().x == -1.0)
		{
			Projectile* pro = new Projectile(sf::Vector2f(a->left - (GAME_TILE_DIM), a->top), a->getDirection());
			pro->drawPlease = false;
			pro->damage = 25;
			arrows.push_back(pro);
			//std::cout << pro->hitbox.getGlobalBounds().left << ", " << pro->hitbox.getGlobalBounds().top << std::endl;
		}
		else if(a->getDirection().y == 1.0)
		{
			Projectile* pro = new Projectile(sf::Vector2f(a->left, a->top + (GAME_TILE_DIM)), a->getDirection());
			pro->drawPlease = false;
			pro->damage = 25;
			arrows.push_back(pro); 
			//std::cout << pro->hitbox.getGlobalBounds().left << ", " << pro->hitbox.getGlobalBounds().top << std::endl;
		}
		else if(a->getDirection().y == -1.0)
		{
			Projectile* pro = new Projectile(sf::Vector2f(a->left, a->top - (GAME_TILE_DIM)), a->getDirection());
			pro->drawPlease = false;
			pro->damage = 25;
			arrows.push_back(pro);
			//std::cout << pro->hitbox.getGlobalBounds().left << ", " << pro->hitbox.getGlobalBounds().top << std::endl;
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

	for (auto iter = hitPointTileList.begin(); iter != hitPointTileList.end();)
	{
		if((*iter)->isHealthZero())
		{
			auto iterToErase = iter;
			iter++;
			delete (*iterToErase);
			*iterToErase = new Tile();
			hitPointTileList.erase(iterToErase);
			continue;
		}

		iter++;
	}
}

void Level::checkHitPointTilesForDmg(float deltaTime)
{
	for (auto it = hitPointTileList.begin(); it != hitPointTileList.end(); it++)
	{
		if((*it)->isWaitOver(deltaTime))
		{
			if(collisionManager->playerSwordCollideWithTile(p.playerSword, *it) && p.playerSword.attacking)
			{
				(*it)->takeDamage();
			}
		}
	}
}

void Level::shakeScreen(float duration, int shakeOff)
{
	screenShake = true;
	screenShakeDuration = duration;
	currentScreenShakeCooldown = 0;
	shakeOffset = shakeOff;
}

void Level::loadSounds()
{
	goliathSound[STOMP1] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("GoliathStomp1")));
	goliathSound[STOMP2] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("GoliathStomp2")));
	goliathSound[STOMP3] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("GoliathStomp3")));
}

void Level::playStompSound()
{
	int sound = rand() % 3;
	goliathSound[sound].play();
}