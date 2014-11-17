
#include "Level.h"

Level::Level(int levelNumber)
	:levelNum(levelNumber), numSect(Global::GetInstance().levelSizes.at("Level " + std::to_string(levelNumber)))
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
	}
}

bool Level::CheckSectionOnScreen(int sectionNum)
{
	return sectList[sectionNum]->inWindow();
}

std::vector<BaseObject*> Level::GetNearTiles(Player& player, bool checkInteractable)
{
	sf::IntRect rect(sf::Vector2i(player.sprite.getPosition().x - PLAYER_DIM/2, player.sprite.getPosition().y - PLAYER_DIM/2), sf::Vector2i(PLAYER_DIM, PLAYER_DIM));
	sf::Vector2i topLeft = sf::Vector2i(rect.left, rect.top);
	sf::Vector2i botRight = sf::Vector2i(rect.left + rect.width, rect.top + rect.height);
	Global g = Global::GetInstance();

	for (int i = 0; i < numSect; i++)
	{
		if (sectList[i]->inWindow())
		{
			//Check and see if the top left of the box is in the current grid
			std::vector<BaseObject*> temp = checkUpperLeftSameGrid(i, rect, topLeft, botRight, checkInteractable);
			if ( temp.size() > 0)
				return temp;
		}
	}
	return std::vector<BaseObject*>();
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

std::vector<BaseObject*> Level::checkUpperLeftSameGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i topLeft, const sf::Vector2i botRight, bool checkInteractable)
{
	Global g = Global::GetInstance();
	if(g.checkPoint(topLeft, sf::IntRect(sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth(), sectList[currentGrid]->getHeight()))))
	{
		//Check to see if the bottom right is in the same grid
		if(g.checkPoint(botRight, sf::IntRect(sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth(), sectList[currentGrid]->getHeight()))))
		{
			//Check to see if the grid is not the last one
			if(currentGrid < numSect-1)
			{
				//Check to see if the lower right corner is in the last col
				return checkLowerRightLastCol(currentGrid, rect, topLeft, botRight, checkInteractable);
			}
			if (currentGrid > 0)
			{
				//Check to see if the upper left corner is in the first col
				return checkUpperLeftFirstCol(currentGrid, rect, topLeft, botRight, checkInteractable);
			}
			//If the grid is the last grid
			else
				if (checkInteractable)
					return sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), botRight - sectList[currentGrid]->getOffset(), false, false);
				else
					return sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), botRight - sectList[currentGrid]->getOffset());

		}
		//If the bottom right corner is not in the same grid
		else
		{
			//Check to see if the bottom right corner is in the next grid
			return checkLowerRightNextGrid(currentGrid, rect, topLeft, botRight, checkInteractable);
		}
	}

	return std::vector<BaseObject*>();
}

std::vector<BaseObject*> Level::checkLowerRightNextGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i topLeft, const sf::Vector2i botRight, bool checkInteractable)
{
	Global g = Global::GetInstance();
	if(g.checkPoint(botRight, sf::IntRect(sectList[currentGrid+1]->getOffset(), sf::Vector2i(sectList[currentGrid+1]->getWidth(), sectList[currentGrid+1]->getHeight()))))
	{
		if (!checkInteractable)
		{
			std::vector<BaseObject*> nearRects = sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth()-1, rect.top + rect.height));
			std::vector<BaseObject*> t1 = sectList[currentGrid+1]->surroundingRects(sf::Vector2i(0, rect.top), 
						sf::Vector2i(rect.left + rect.width - sectList[currentGrid+1]->getOffset().x, rect.top + rect.height));
			nearRects.insert(nearRects.end(), t1.begin(), t1.end());
			return nearRects;
		}
		else
		{
			std::vector<BaseObject*> nearRects = sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), sf::Vector2i(sectList[currentGrid]->getWidth()-1, rect.top + rect.height), false, false);
			std::vector<BaseObject*> t1 = sectList[currentGrid+1]->surroundingRects(sf::Vector2i(0, rect.top), 
						sf::Vector2i(rect.left + rect.width - sectList[currentGrid+1]->getOffset().x, rect.top + rect.height), false, false);
			nearRects.insert(nearRects.end(), t1.begin(), t1.end());
			return nearRects;
		}
	}
	return std::vector<BaseObject*>();
}

std::vector<BaseObject*> Level::checkLowerRightLastCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i topLeft, const sf::Vector2i botRight, bool checkInteractable)
{
	if ((rect.left + rect.width - sectList[currentGrid]->getOffset().x)/ GAME_TILE_DIM == sectList[currentGrid]->getGridDim().x-1) 
	{
		std::vector<BaseObject*> nearRects = sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), 
						botRight - sectList[currentGrid]->getOffset());

		std::vector<BaseObject*> t1 = sectList[currentGrid+1]->surroundingRects(sf::Vector2i(0, rect.top), sf::Vector2i(0, rect.top + rect.height), false);
		nearRects.insert(nearRects.end(), t1.begin(), t1.end());
		return nearRects;
	}
	//If not in the last col 
	else
		return sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(),
				botRight - sectList[currentGrid]->getOffset());
}


std::vector<BaseObject*> Level::checkUpperLeftFirstCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i topLeft, const sf::Vector2i botRight, bool checkInteractable)
{
	if ((rect.left - sectList[currentGrid]->getOffset().x) / GAME_TILE_DIM < 1) 
	{
		std::vector<BaseObject*> nearRects = sectList[currentGrid]->surroundingRects(topLeft- sectList[currentGrid]->getOffset(), 
													botRight - sectList[currentGrid]->getOffset());
		std::vector<BaseObject*> t1 = sectList[currentGrid-1]->surroundingRects(sf::Vector2i(sectList[currentGrid-1]->getWidth()-1, rect.top), 
					sf::Vector2i(sectList[currentGrid-1]->getWidth()-1, rect.top + rect.height), false);
		nearRects.insert(nearRects.end(), t1.begin(), t1.end());
		return nearRects;
	}
	//If not in the last col 
	else
		return sectList[currentGrid]->surroundingRects(topLeft - sectList[currentGrid]->getOffset(), botRight - sectList[currentGrid]->getOffset());
}