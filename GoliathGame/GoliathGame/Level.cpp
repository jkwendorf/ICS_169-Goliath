
#include "Level.h"

Level::Level(int levelNumber)
	:levelNum(levelNumber), numSect(Global::GetInstance().levelSizes.at("Level " + std::to_string(levelNumber))),
	levelWidth(0), loadedTitles(false)
{
	LoadLevel();
}

Level::~Level()
{
	for (int i = 0; i < numSect; i++)
		delete sectList[i];
	delete[] sectList;
}

Level::Level()
{}
	
void Level::LoadLevel()
{
	sectList = new Section*[numSect];
	for (int i = 0; i < numSect; i++)
	{
		std::string temp = "level" + std::to_string(levelNum) + "num" + std::to_string(i);
		if(i==0)
			sectList[i] = new Section(i, temp, sf::Vector2i(0,0));
		else
			sectList[i] = new Section(i, temp, sf::Vector2i(i*sectList[i-1]->getWidth(), 0));
		levelWidth = levelWidth + sectList[i]->getWidth();
	}
	
	sf::Texture* texture = TextureManager::GetInstance().retrieveTexture(Global::GetInstance().levelTileSheets.at("Level " + std::to_string(levelNum)));
	Global::GetInstance().SetUpTileSheet(texture);
}

bool Level::CheckSectionOnScreen(int sectionNum)
{
	return sectList[sectionNum]->inWindow();
}

void Level::GetCollidableTiles(Player& player, std::vector<Tile*>& nearTiles)
{
	sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x - PLAYER_DIM_X/2, player.sprite.getPosition().y - PLAYER_DIM_Y/2), sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y));
	GetNearTiles(rect, nearTiles);
	return;
}

bool Level::NearInteractableTiles(Player& player, std::vector<Tile*>& nearTiles)
{
	sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x - PLAYER_DIM_X/2, player.sprite.getPosition().y - PLAYER_DIM_Y/2), sf::Vector2i(PLAYER_DIM_X, PLAYER_DIM_Y));
	GetNearTiles(rect, nearTiles, true);
	if(nearTiles.size() > 0)
		return true;
	return false; 
}

void Level::GetGrapplableTiles(Player& player, std::vector<Tile*>& nearTiles)
{
	//std::cout << player.sprite.getPosition().y - PLAYER_DIM/2 << std::endl;
	//std::cout << player.hShot.grappleLength << std::endl;
	if(player.sprite.getPosition().y - PLAYER_DIM_Y/2 - player.hShot.grappleLength >= 0)
	{
		if (!player.facingRight)
		{
			sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x - PLAYER_DIM_X/2 - player.hShot.grappleLength, player.sprite.getPosition().y - PLAYER_DIM_Y/2 - player.hShot.grappleLength),
				sf::Vector2i(player.hShot.grappleLength, player.hShot.grappleLength));
			GetNearTiles(rect, nearTiles, true, true);
			return;
		}
		else
		{
			sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x + PLAYER_DIM_X/2, player.sprite.getPosition().y - PLAYER_DIM_Y/2 - player.hShot.grappleLength),
				sf::Vector2i(player.hShot.grappleLength, player.hShot.grappleLength));
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

void Level::GetNearTiles(sf::IntRect& rect, std::vector<Tile*>& nearTiles, bool checkBoxOnly, bool grapple)
{
	sf::Vector2i topLeft = sf::Vector2i(rect.left, rect.top);
	sf::Vector2i botRight = sf::Vector2i(rect.left + rect.width, rect.top + rect.height);
	

	for (int i = 0; i < numSect; i++)
	{
		if (sectList[i]->inWindow())
		{
			//Check and see if the top left of the box is in the current grid
			checkUpperLeftSameGrid(i, rect, topLeft, botRight, nearTiles, checkBoxOnly, grapple);
			if ( nearTiles.size() > 0)
				return;
		}
	}
}

void Level::update(float deltaTime)
{
	//player.update(deltaTime);
	for(int i = 0; i < numSect; i++)
	{
		sectList[i]->update(deltaTime);
	}
}

void Level::draw(sf::RenderWindow& w)
{
	//player.draw(w);
	for(int i = 0; i < numSect; i++)
	{
		sectList[i]->draw(w);
	}

}

void Level::checkUpperLeftSameGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
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
}

void Level::checkLowerRightNextGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
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
				std::vector<Tile*> t1;
				sectList[currentGrid+1]->surroundingRects(sf::Vector2i(0, rect.top), 
							sf::Vector2i(rect.left + rect.width - sectList[currentGrid+1]->getOffset().x, rect.top + rect.height), t1);
				nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
				return;
			}
			else
			{
				if (grapple)
				{
					sectList[currentGrid]->checkGrapple(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth()-1, rect.top + rect.height), nearTiles);
					std::vector<Tile*> t1;
					sectList[currentGrid+1]->checkGrapple(sf::Vector2i(0, rect.top), 
								sf::Vector2i(rect.left + rect.width - sectList[currentGrid+1]->getOffset().x, rect.top + rect.height), t1);
					nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
					return;
				}
				else
				{
					sectList[currentGrid]->checkInteractable(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth()-1, rect.top + rect.height), nearTiles);
					std::vector<Tile*> t1;
					sectList[currentGrid+1]->checkInteractable(sf::Vector2i(0, rect.top), 
								sf::Vector2i(rect.left + rect.width - sectList[currentGrid+1]->getOffset().x, rect.top + rect.height), t1);
					nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
					return;
				}
			}
		}
	}
}

void Level::checkLowerRightLastCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
													   const sf::Vector2i& botRight, std::vector<Tile*>& nearTiles)
{
	if ((rect.left + rect.width - sectList[currentGrid]->getOffset().x)/ GAME_TILE_DIM == sectList[currentGrid]->getGridDim().x-1) 
	{
		sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), 
						botRight - sectList[currentGrid]->getOffset(), nearTiles);

		std::vector<Tile*> t1;
		sectList[currentGrid+1]->surroundingRects(sf::Vector2i(0, rect.top), sf::Vector2i(0, rect.top + rect.height), t1, false);
		nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
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

void Level::checkUpperLeftFirstCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
													   const sf::Vector2i& botRight, std::vector<Tile*>& nearTiles)
{
	if ((rect.left - sectList[currentGrid]->getOffset().x) / GAME_TILE_DIM < 1) 
	{
		sectList[currentGrid]->surroundingRects(topLeft- sectList[currentGrid]->getOffset(), 
													botRight - sectList[currentGrid]->getOffset(), nearTiles);
		std::vector<Tile*> t1;
		sectList[currentGrid-1]->surroundingRects(sf::Vector2i(sectList[currentGrid-1]->getWidth()-1, rect.top), 
					sf::Vector2i(sectList[currentGrid-1]->getWidth()-1, rect.top + rect.height), t1, false);
		nearTiles.insert(nearTiles.end(), t1.begin(), t1.end());
		return;
	}
	//If not in the last col 
	else
	{
		sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), botRight - sectList[currentGrid]->getOffset(), nearTiles);
		return;
	}
	
}

int Level::getLevelWidth()
{
	return levelWidth;
}