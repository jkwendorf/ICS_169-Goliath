
#include "Room.h"

Room::Room(int levelNumber, int roomNumber, std::vector<std::shared_ptr<Enemy>> &enemyList, std::vector<Tile*> &arrowTileList, std::list<Tile*> &destructTileList)
	:roomNum(roomNumber), numSect(Global::GetInstance().roomSizes.at("Level" + std::to_string(levelNumber) + "Room" + std::to_string(roomNumber)).roomSize),
	roomWidth(0), roomHeight(0), loadedTitles(false), bg(levelNumber, roomNumber)
{
	LoadRoom(levelNumber, enemyList, arrowTileList, destructTileList);
	//Music
	if (!roomMusic.openFromFile("media/sound/Testlevel1SoTC.wav"))
	{
		std::cout << "Error for loading file" << std::endl;
	}
	roomMusic.setLoop(true);
	roomMusic.play();
}

Room::~Room()
{
	std::cout << "Deleting the room" << std::endl;
	for (int i = 0; i < numSect; i++)
		delete sectList[i];
	delete[] sectList;
	roomMusic.stop();
}
	
void Room::LoadRoom(int levelNumber, std::vector<std::shared_ptr<Enemy>> &enemyList, std::vector<Tile*> &arrowTileList, std::list<Tile*> &destructTileList)
{
	sectList = new Section*[numSect];
	int totalWidth = 0;
	for (int i = 0; i < numSect; i++)
	{
		std::string temp = "level" + std::to_string(levelNumber) + "room" + std::to_string(roomNum) + "section" + std::to_string(i+1);
		if(i==0)
		{
			sectList[i] = new Section(i, temp, sf::Vector2f(0,0), enemyList, arrowTileList, destructTileList);
			if(sectList[i]->getStartPos().x != -999)
				startPos = sectList[i]->getStartPos();
		}
		else
		{
			sectList[i] = new Section(i, temp, sf::Vector2f(roomWidth, 0), enemyList, arrowTileList, destructTileList);
			if(sectList[i]->getStartPos().x != -999)
				startPos = sectList[i]->getStartPos();
		}
		roomWidth = roomWidth + sectList[i]->getWidth();

		if(roomHeight < sectList[i]->getHeight())
			roomHeight = sectList[i]->getHeight();
	}
	
	//std::cout << Global::GetInstance().roomTileSheets. << std::endl;
	sf::Texture* texture = TextureManager::GetInstance().retrieveTexture(Global::GetInstance().roomTileSheets.at("Level" + std::to_string(levelNumber) + "Room" + std::to_string(roomNum)));
	Global::GetInstance().SetUpTileSheet(texture);
}

bool Room::CheckSectionOnScreen(int sectionNum)
{
	return sectList[sectionNum]->inWindow();
}

void Room::GetCollidableTiles(BaseObject& obj, sf::Vector2f& dim, std::vector<Tile*>& nearTiles)
{
	//sf::FloatRect rect(sf::Vector2f(obj.sprite.getPosition().x - dim.x/2, obj.sprite.getPosition().y - dim.y/2), sf::Vector2f(dim.x, dim.y));
	//std::cout << obj.sprite.getGlobalBounds().left << ", " << obj.sprite.getGlobalBounds().top << ", " << obj.sprite.getGlobalBounds().width << ", ";
	//std::cout <<  obj.sprite.getGlobalBounds().height << std::endl;
	GetNearTiles(obj.sprite.getGlobalBounds(), nearTiles);
	return;
}

int Room::NearInteractableTiles(BaseObject& obj)
{
	std::vector<Tile*> nearTiles;
	//sf::IntRect rect(sf::Vector2f(obj.sprite.getPosition().x - PLAYER_DIM_X/2, obj.sprite.getPosition().y - PLAYER_DIM_Y/2), sf::Vector2f(PLAYER_DIM_X, PLAYER_DIM_Y));
	GetNearTiles(obj.sprite.getGlobalBounds(), nearTiles, true);
	if(nearTiles.size() > 0)
		return nearTiles[0]->getTileNum();
	return -999; 
}

void Room::GetGrapplableTiles(Player& player, std::vector<Tile*>& nearTiles)
{
	//*Global::GetInstance().debugLog << "Player Pos: " << player.sprite.getPosition().x << ", " << player.sprite.getPosition().y << "---";
	if(player.sprite.getPosition().y - PLAYER_DIM_Y/2 - player.hShot.grappleBox >= 0)
	{
		if (!player.facingRight)
		{
			sf::FloatRect rect(sf::Vector2f(player.sprite.getPosition().x /*- PLAYER_DIM_X/2 */ - player.hShot.grappleBox, 
				player.sprite.getPosition().y /*- PLAYER_DIM_Y/2 */ - player.hShot.grappleBox),
				sf::Vector2f(player.hShot.grappleBox, player.hShot.grappleBox));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
		else
		{
			sf::FloatRect rect(sf::Vector2f(player.sprite.getPosition().x,
				player.sprite.getPosition().y /*- PLAYER_DIM_Y/2 */ - player.hShot.grappleBox),
				sf::Vector2f(player.hShot.grappleBox, player.hShot.grappleBox));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
	}
	else
	{
		//These two cases do not work need to fix the Grant Walker
		if (!player.facingRight)
		{
			sf::FloatRect rect(sf::Vector2f(player.sprite.getPosition().x /*- PLAYER_DIM_X/2 */ - player.hShot.grappleBox, 0),
				sf::Vector2f(player.hShot.grappleBox, player.sprite.getPosition().y));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
		else
		{
			sf::FloatRect rect(sf::Vector2f(player.sprite.getPosition().x + PLAYER_DIM_X/2, 0),
				sf::Vector2f(player.hShot.grappleBox, player.sprite.getPosition().y));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
		
	}
}

void Room::GetNearTiles(sf::FloatRect& rect, std::vector<Tile*>& nearTiles, bool checkBoxOnly, bool grapple)
{
	sf::Vector2f topLeft = sf::Vector2f(rect.left, rect.top);
	sf::Vector2f botRight = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
	
	for (int i = 0; i < numSect; i++)
	{
		if (sectList[i]->inWindow())
		{
			//Check and see if the top left of the box is in the current grid
			if(i == 1 && topLeft.x < 0)
			{
				topLeft.x = (0 + PLAYER_DIM_X /2);
				botRight.x = (0 + PLAYER_DIM_X /2);
			}
			if (i == numSect-1 && topLeft.x > sectList[i]->getOffset().x + sectList[i]->getWidth())
			{
				topLeft.x = sectList[i]->getOffset().x + sectList[i]->getWidth() - 1;
				botRight.x = sectList[i]->getOffset().x + sectList[i]->getWidth() - 1;
			}
			checkUpperLeftSameGrid(i, rect, topLeft, botRight, nearTiles, checkBoxOnly, grapple);
			if ( nearTiles.size() > 0)
				return;
		}
	}
}

void Room::update(float deltaTime)
{
	bg.update(deltaTime);
}

void Room::draw(sf::RenderWindow& w)
{
	bg.draw(w);
	for(int i = 0; i < numSect; i++)
	{
		sectList[i]->draw(w);
	}

}

void Room::checkUpperLeftSameGrid(int currentGrid, sf::FloatRect& rect, const sf::Vector2f& topLeft, 
													   const sf::Vector2f& botRight, std::vector<Tile*>& nearTiles, 
													   bool checkBoxOnly, bool grapple)
{
	Global g = Global::GetInstance();
	if(g.checkPoint(topLeft, sf::FloatRect(sectList[currentGrid]->getOffset(), sf::Vector2f(sectList[currentGrid]->getWidth(), sectList[currentGrid]->getHeight()))))
	{
		//Check to see if the bottom right is in the same grid
		if(g.checkPoint(botRight, sf::FloatRect(sectList[currentGrid]->getOffset(), sf::Vector2f(sectList[currentGrid]->getWidth(), sectList[currentGrid]->getHeight()))))
		{
			//Check to see if the grid is not the last one
			if(currentGrid < numSect-1 && !checkBoxOnly)
			{
				//Check to see if the lower right corner is in the last col
				checkLowerRightLastCol(currentGrid, rect, topLeft, botRight, nearTiles);
				return;
			}
			if (currentGrid > 0 && !checkBoxOnly)
			{
				//Check to see if the upper left corner is in the first col
				checkUpperLeftFirstCol(currentGrid, rect, topLeft, botRight, nearTiles);
				return;
			}
			//If the grid is the last grid
			else
				if (checkBoxOnly)
				{
					if (grapple)
					{
						sectList[currentGrid]->checkGrapple(topLeft - sectList[currentGrid]->getOffset(), botRight - sectList[currentGrid]->getOffset(), nearTiles);
						return;
					}
					sectList[currentGrid]->checkInteractable(topLeft - sectList[currentGrid]->getOffset(), botRight - sectList[currentGrid]->getOffset(), nearTiles);
					return;
				}
				else
				{
					sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), botRight - sectList[currentGrid]->getOffset(), nearTiles);
					return;
				}
		}
		//If the bottom right corner is not in the same grid
		else
		{
			//Check to see if the bottom right corner is in the next grid
			checkLowerRightNextGrid(currentGrid, rect, topLeft, botRight, nearTiles, checkBoxOnly, grapple);
			return;
		}
	}
	//If the top right corner is not in the grid 
	else
	{
		if (grapple)
		{		
			//Set the top left y position = 0	
			sectList[currentGrid]->checkGrapple(sf::Vector2f(topLeft.x < 0 ? 0 : topLeft.x, topLeft.y < 0 ? 0 : topLeft.y), 
				botRight - sectList[currentGrid]->getOffset(), nearTiles);
			return;
		}
	
	}
}

void Room::checkLowerRightNextGrid(int currentGrid, sf::FloatRect& rect, const sf::Vector2f& topLeft, 
														const sf::Vector2f& botRight, std::vector<Tile*>& nearTiles,
														bool checkBoxOnly, bool grapple)
{
	Global g = Global::GetInstance();
	//If check to see if it is not the last grid
	if(currentGrid + 1 < numSect)
	{
		if(g.checkPoint(botRight, sf::FloatRect(sectList[currentGrid+1]->getOffset(), sf::Vector2f(sectList[currentGrid+1]->getWidth(), sectList[currentGrid+1]->getHeight()))))
		{
			if(!checkBoxOnly)
			{
				sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2f(sectList[currentGrid]->getWidth()-1, rect.top + rect.height), nearTiles);
				//std::vector<Tile*> t1;
				sectList[currentGrid+1]->surroundingRects(sf::Vector2f(0, topLeft.y), 
					sf::Vector2f(botRight.x - sectList[currentGrid+1]->getOffset().x, botRight.y), nearTiles);
				//nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
				return;
			}
			else
			{
				if (grapple)
				{
					sectList[currentGrid]->checkGrapple(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2f(sectList[currentGrid]->getWidth()-1, topLeft.y), nearTiles);
					//std::vector<Tile*> t1;
					sectList[currentGrid+1]->checkGrapple(sf::Vector2f(0, topLeft.y), 
								sf::Vector2f(botRight.x - sectList[currentGrid+1]->getOffset().x, botRight.y), nearTiles);
					//nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
					return;
				}
				else
				{
					sectList[currentGrid]->checkInteractable(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2f(sectList[currentGrid]->getWidth()-1, topLeft.y), nearTiles);
					//std::vector<Tile*> t1;
					sectList[currentGrid+1]->checkInteractable(sf::Vector2f(0, topLeft.y), 
								sf::Vector2f(botRight.x - sectList[currentGrid+1]->getOffset().x, botRight.x),nearTiles);
					//nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
					return;
				}
			}
		}
	}
	else
	{
		//std::cout << "Testing: " << botRight.x << " : " << sectList[currentGrid]->getWidth() << std::endl;
		if (grapple)
		{			
			sectList[currentGrid]->checkGrapple(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2f(sectList[currentGrid]->getOffset().x + sectList[currentGrid]->getWidth() ,botRight.y), nearTiles);
			return;
		}

	}
}

void Room::checkLowerRightLastCol(int currentGrid, sf::FloatRect& rect, const sf::Vector2f& topLeft, 
													   const sf::Vector2f& botRight, std::vector<Tile*>& nearTiles)
{
	if ((botRight.x - sectList[currentGrid]->getOffset().x)/ GAME_TILE_DIM == sectList[currentGrid]->getGridDim().x-1) 
	{
		sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), 
						botRight - sectList[currentGrid]->getOffset(), nearTiles);

		//std::vector<Tile*> t1;
		sectList[currentGrid+1]->surroundingRects(sf::Vector2f(0, topLeft.y), sf::Vector2f(0, botRight.y), nearTiles, false);
		//nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
		return;
	}
	//If not in the last col 
	else
	{
		sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(),
				botRight - sectList[currentGrid]->getOffset(), nearTiles);
		return;
	}
}

void Room::checkUpperLeftFirstCol(int currentGrid, sf::FloatRect& rect, const sf::Vector2f& topLeft, 
													   const sf::Vector2f& botRight, std::vector<Tile*>& nearTiles)
{
	if ((rect.left - sectList[currentGrid]->getOffset().x) / GAME_TILE_DIM < 1) 
	{
		sectList[currentGrid]->surroundingRects(topLeft- sectList[currentGrid]->getOffset(), 
													botRight - sectList[currentGrid]->getOffset(), nearTiles);
		//std::vector<Tile*> t1;
		sectList[currentGrid-1]->surroundingRects(sf::Vector2f(sectList[currentGrid-1]->getWidth()-1, topLeft.y), 
					sf::Vector2f(sectList[currentGrid-1]->getWidth()-1, botRight.y), nearTiles, false);
		//nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
		return;
	}
	//If not in the last col 
	else
	{
		sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), botRight - sectList[currentGrid]->getOffset(), nearTiles);
		return;
	}
	
}

int Room::getRoomNumber()
{
	return roomNum;
}

int Room::getroomWidth()
{
	return roomWidth;
}

int Room::getroomHeight()
{
	return sectList[0]->getHeight();
}

sf::Vector2f Room::getStartPos()
{
	return startPos;
}