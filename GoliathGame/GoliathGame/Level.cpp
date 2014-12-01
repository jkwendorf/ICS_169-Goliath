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
	enemyList.push_back(new Enemy("Test", 1000, 1000));
	enemyList.push_back(new Enemy("Test", 700, 400));
}

Level::~Level(void)
{
	delete currentRoom;
	delete inputManager;
	delete collisionManager;
	for(Enemy* e : enemyList)
	{
		delete e;
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
//	std::cout << p.sprite.getPosition().x << ", " << p.sprite.getPosition().y <<  std::endl;

	currentRoom->GetCollidableTiles(p, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), nearTiles);

	collisionManager->setNearByTiles(nearTiles);
	collisionManager->setGrapplableTiles(nearTiles2);
	p.hShot.hookedOnSomething = collisionManager->hookCollisionDetection(p.hShot);
	inputManager->update(p, collisionManager, deltaTime);

	//p.isFalling = !collisionManager->playerCollisionDetection(p);
	//p.update(deltaTime);
	p.playerUpdate(&view, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), deltaTime);

	for (Enemy* e : enemyList)
	{
		currentRoom->GetCollidableTiles(*e, sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y), enemyTiles);
		if(enemyTiles.size() > 0)
		{
			collisionManager->setNearByTiles(enemyTiles);
		}
		e->enemyUpdate(collisionManager, deltaTime, sf::Vector2i(currentRoom->getroomWidth(), currentRoom->getroomHeight()), p.sprite.getPosition());
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
	for(Enemy* e : enemyList)
	{
		e->draw(window);
	//	enemyNum++;
	//	std::cout << "Enemy #" << enemyNum;
	}
	window.setView(view);
}

