
#include "Room.h"

Room::Room(int levelNumber, int roomNumber, std::vector<std::unique_ptr<Enemy>> &enemyList)
	:roomNum(roomNumber), numSect(Global::GetInstance().roomSizes.at("Room " + std::to_string(roomNumber))),
	roomWidth(0), roomHeight(0), loadedTitles(false)
{
	LoadRoom(levelNumber, enemyList);
}

Room::~Room()
{
	std::cout << "Deleting the room" << std::endl;
	for (int i = 0; i < numSect; i++)
		delete sectList[i];
	delete[] sectList;
}

Room::Room()
{}
	
void Room::LoadRoom(int levelNumber, std::vector<std::unique_ptr<Enemy>> &enemyList)
{
	sectList = new Section*[numSect];
	int totalWidth = 0;
	for (int i = 0; i < numSect; i++)
	{
		std::string temp = "level" + std::to_string(levelNumber) + "room" + std::to_string(roomNum) + "section" + std::to_string(i+1);
		if(i==0)
		{
			sectList[i] = new Section(i, temp, sf::Vector2i(0,0), enemyList);
			if(sectList[i]->getStartPos().x != -999)
				startPos = sectList[i]->getStartPos();
		}
		else
		{
			sectList[i] = new Section(i, temp, sf::Vector2i(roomWidth, 0), enemyList);
			if(sectList[i]->getStartPos().x != -999)
				startPos = sectList[i]->getStartPos();
		}
		roomWidth = roomWidth + sectList[i]->getWidth();

		if(roomHeight < sectList[i]->getHeight())
			roomHeight = sectList[i]->getHeight();
	}
	
	//std::cout << Global::GetInstance().roomTileSheets. << std::endl;
	sf::Texture* texture = TextureManager::GetInstance().retrieveTexture(Global::GetInstance().roomTileSheets.at("Room " + std::to_string(roomNum)));
	Global::GetInstance().SetUpTileSheet(texture);
}

bool Room::CheckSectionOnScreen(int sectionNum)
{
	return sectList[sectionNum]->inWindow();
}

void Room::GetCollidableTiles(BaseObject& obj, sf::Vector2i& dim, std::vector<Tile*>& nearTiles)
{
	sf::IntRect rect(sf::Vector2i(obj.sprite.getPosition().x - dim.x/2, obj.sprite.getPosition().y - dim.y/2), sf::Vector2i(dim.x, dim.y));
	GetNearTiles(rect, nearTiles);
	return;
}

bool Room::NearInteractableTiles(BaseObject& obj)
{
	std::vector<Tile*> nearTiles;
	sf::IntRect rect(sf::Vector2i(obj.sprite.getPosition().x - PLAYER_DIM_X/2, obj.sprite.getPosition().y - PLAYER_DIM_Y/2), sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y));
	GetNearTiles(rect, nearTiles, true);
	if(nearTiles.size() > 0)
		return true;
	return false; 
}

void Room::GetGrapplableTiles(Player& player, std::vector<Tile*>& nearTiles)
{
	//std::cout << player.sprite.getPosition().y - PLAYER_DIM/2 << std::endl;
	//std::cout << player.hShot.grappleLength << std::endl;
	if(player.sprite.getPosition().y - PLAYER_DIM_Y/2 - player.hShot.grappleLength >= 0)
	{
		if (!player.facingRight)
		{
			sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x - PLAYER_DIM_X/2 - player.hShot.grappleLength, player.sprite.getPosition().y - PLAYER_DIM_Y/2 - player.hShot.grappleLength),
				sf::Vector2i(player.hShot.grappleLength + PLAYER_DIM_X/2, player.hShot.grappleLength + PLAYER_DIM_X/2));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
		else
		{
			sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x + PLAYER_DIM_X/2, player.sprite.getPosition().y - PLAYER_DIM_Y/2 - player.hShot.grappleLength),
				sf::Vector2i(player.hShot.grappleLength + PLAYER_DIM_X/2, player.hShot.grappleLength + PLAYER_DIM_X/2));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
	}
	else
	{
		if (!player.facingRight)
		{
			sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x - PLAYER_DIM_X/2 - player.hShot.grappleLength, player.sprite.getPosition().y - PLAYER_DIM_Y/2),
				sf::Vector2i(player.hShot.grappleLength, 0));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
		else
		{
			sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x + PLAYER_DIM_X/2, player.sprite.getPosition().y - PLAYER_DIM_Y/2),
				sf::Vector2i(player.hShot.grappleLength, 0));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
		
	}
}

void Room::GetNearTiles(sf::IntRect& rect, std::vector<Tile*>& nearTiles, bool checkBoxOnly, bool grapple)
{
	sf::Vector2i topLeft = sf::Vector2i(rect.left, rect.top);
	sf::Vector2i botRight = sf::Vector2i(rect.left + rect.width, rect.top + rect.height);
	
	for (int i = 0; i < numSect; i++)
	{
		if (sectList[i]->inWindow())
		{
			//Check and see if the top left of the box is in the current grid
			if(i == 1 && topLeft.x < 0)
			{
				topLeft.x = (0 + PLAYER_DIM_X /2);
				botRight.x = (0 + PLAYER_DIM_X /2);
				std::cout << "TopLeft: " << topLeft.x << ", " << topLeft.y << std::endl;
				std::cout << "BotRight: " << botRight.x << ", " << botRight.y << std::endl;
			}
			if (i == numSect-1 && topLeft.x > sectList[i]->getOffset().x + sectList[i]->getWidth())
			{
				topLeft.x = sectList[i]->getOffset().x + sectList[i]->getWidth() - 1;
				botRight.x = sectList[i]->getOffset().x + sectList[i]->getWidth() - 1;
				std::cout << "TopLeft: " << topLeft.x << ", " << topLeft.y << std::endl;
				std::cout << "BotRight: " << botRight.x << ", " << botRight.y << std::endl;
			}
			checkUpperLeftSameGrid(i, rect, topLeft, botRight, nearTiles, checkBoxOnly, grapple);
			if ( nearTiles.size() > 0)
				return;
		}
	}
}

void Room::update(float deltaTime)
{
	//player.update(deltaTime);
	for(int i = 0; i < numSect; i++)
	{
		sectList[i]->update(deltaTime);
	}
}

void Room::draw(sf::RenderWindow& w)
{
	//player.draw(w);
	for(int i = 0; i < numSect; i++)
	{
		sectList[i]->draw(w);
	}

}

void Room::checkUpperLeftSameGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
													   const sf::Vector2i& botRight, std::vector<Tile*>& nearTiles, 
													   bool checkBoxOnly, bool grapple)
{
	Global g = Global::GetInstance();
	if(g.checkPoint(topLeft, sf::IntRect(sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth(), sectList[currentGrid]->getHeight()))))
	{
		//Check to see if the bottom right is in the same grid
		if(g.checkPoint(botRight, sf::IntRect(sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth(), sectList[currentGrid]->getHeight()))))
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
	//else
	//{
	//	std::cout << std::endl;
	//}
}

void Room::checkLowerRightNextGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
														const sf::Vector2i& botRight, std::vector<Tile*>& nearTiles,
														bool checkBoxOnly, bool grapple)
{
	Global g = Global::GetInstance();
	if(currentGrid + 1 < numSect)
	{
		if(g.checkPoint(botRight, sf::IntRect(sectList[currentGrid+1]->getOffset(), sf::Vector2i(sectList[currentGrid+1]->getWidth(), sectList[currentGrid+1]->getHeight()))))
		{
			if(!checkBoxOnly)
			{
				sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth()-1, rect.top + rect.height), nearTiles);
				//std::vector<Tile*> t1;
				sectList[currentGrid+1]->surroundingRects(sf::Vector2i(0, topLeft.y), 
					sf::Vector2i(botRight.x - sectList[currentGrid+1]->getOffset().x, botRight.y), nearTiles);
				//nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
				return;
			}
			else
			{
				if (grapple)
				{
					sectList[currentGrid]->checkGrapple(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth()-1, topLeft.y), nearTiles);
					//std::vector<Tile*> t1;
					sectList[currentGrid+1]->checkGrapple(sf::Vector2i(0, topLeft.y), 
								sf::Vector2i(botRight.x - sectList[currentGrid+1]->getOffset().x, botRight.y), nearTiles);
					//nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
					return;
				}
				else
				{
					sectList[currentGrid]->checkInteractable(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth()-1, topLeft.y), nearTiles);
					//std::vector<Tile*> t1;
					sectList[currentGrid+1]->checkInteractable(sf::Vector2i(0, topLeft.y), 
								sf::Vector2i(botRight.x - sectList[currentGrid+1]->getOffset().x, botRight.x),nearTiles);
					//nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
					return;
				}
			}
		}
	}
}

void Room::checkLowerRightLastCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
													   const sf::Vector2i& botRight, std::vector<Tile*>& nearTiles)
{
	if ((botRight.x - sectList[currentGrid]->getOffset().x)/ GAME_TILE_DIM == sectList[currentGrid]->getGridDim().x-1) 
	{
		sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), 
						botRight - sectList[currentGrid]->getOffset(), nearTiles);

		//std::vector<Tile*> t1;
		sectList[currentGrid+1]->surroundingRects(sf::Vector2i(0, topLeft.y), sf::Vector2i(0, botRight.y), nearTiles, false);
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

void Room::checkUpperLeftFirstCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
													   const sf::Vector2i& botRight, std::vector<Tile*>& nearTiles)
{
	if ((rect.left - sectList[currentGrid]->getOffset().x) / GAME_TILE_DIM < 1) 
	{
		sectList[currentGrid]->surroundingRects(topLeft- sectList[currentGrid]->getOffset(), 
													botRight - sectList[currentGrid]->getOffset(), nearTiles);
		//std::vector<Tile*> t1;
		sectList[currentGrid-1]->surroundingRects(sf::Vector2i(sectList[currentGrid-1]->getWidth()-1, topLeft.y), 
					sf::Vector2i(sectList[currentGrid-1]->getWidth()-1, botRight.y), nearTiles, false);
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
	return roomHeight;
}

sf::Vector2f Room::getStartPos()
{
	return startPos;
}