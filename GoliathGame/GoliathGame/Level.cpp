
#include "Level.h"

Level::Level(int levelNumber)
	:levelNum(levelNumber), numSect(Global::GetInstance().levelSizes.at("Level " + std::to_string(levelNumber))),
	levelWidth(0)
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
}

bool Level::CheckSectionOnScreen(int sectionNum)
{
	return sectList[sectionNum]->inWindow();
}

std::vector<BaseObject*> Level::GetNearTiles(sf::IntRect& rect)
{
	std::vector<BaseObject*> nearRects;
	sf::Vector2i topLeft = sf::Vector2i(rect.left, rect.top);
	sf::Vector2i botRight = sf::Vector2i(rect.left + rect.width, rect.top + rect.height);
	Global g = Global::GetInstance();
	for (int i = 0; i < numSect; i++)
	{
		if (sectList[i]->inWindow())
		{
			//Check and see if the top left of the box is in the current grid
			if(g.checkPoint(topLeft, sf::IntRect(sectList[i]->getOffset(), sf::Vector2i(sectList[i]->getWidth(), sectList[i]->getHeight()))))
			{
				//Check to see if the bottom right is in the same grid
				if(g.checkPoint(botRight, sf::IntRect(sectList[i]->getOffset(), sf::Vector2i(sectList[i]->getWidth(), sectList[i]->getHeight()))))
				{
					//Check to see if the grid is not the last one
					if(i < numSect-1)
					{
						//Check to see if the lower right corner is in the last col
						if ((rect.left + rect.width - sectList[i]->getOffset().x)/ GAME_TILE_DIM == sectList[i]->getGridDim().x-1) 
						{
							nearRects = sectList[i]->surroundingRects(topLeft - sectList[i]->getOffset(), 
											botRight - sectList[i]->getOffset());

							std::vector<BaseObject*> t1 = sectList[i+1]->surroundingRects(sf::Vector2i(0, rect.top), sf::Vector2i(0, rect.top + rect.height), false);
							nearRects.insert(nearRects.end(), t1.begin(), t1.end());
							return nearRects;
						}
						//If not in the last col 
						else
							return sectList[i]->surroundingRects(topLeft - sectList[i]->getOffset(),
									botRight - sectList[i]->getOffset());
					}
					if ( i > 0)
					{
						//Check to see if the upper left corner is in the first col
						if ((rect.left - sectList[i]->getOffset().x) / GAME_TILE_DIM < 1) 
						{
							nearRects = sectList[i]->surroundingRects(topLeft- sectList[i]->getOffset(), botRight - sectList[i]->getOffset());
							std::vector<BaseObject*> t1 = sectList[i-1]->surroundingRects(sf::Vector2i(sectList[i-1]->getWidth()-1, rect.top), 
										sf::Vector2i(sectList[i-1]->getWidth()-1, rect.top + rect.height), false);
							nearRects.insert(nearRects.end(), t1.begin(), t1.end());
							return nearRects;
						}
						//If not in the last col 
						else
							return sectList[i]->surroundingRects(topLeft - sectList[i]->getOffset(), botRight - sectList[i]->getOffset());
					}
					//If the grid is the last grid
					else
						return sectList[i]->surroundingRects(topLeft - sectList[i]->getOffset(), botRight - sectList[i]->getOffset());
				}
				//If the bottom right corner is not in the same grid
				else
				{
					//Check to see if the bottom right corner is in the next grid
					if(g.checkPoint(botRight, sf::IntRect(sectList[i+1]->getOffset(), sf::Vector2i(sectList[i+1]->getWidth(), sectList[i+1]->getHeight()))))
					{
						nearRects = sectList[i]->surroundingRects(topLeft - sectList[i]->getOffset(), sf::Vector2i(sectList[i]->getWidth()-1, rect.top + rect.height));
						std::vector<BaseObject*> t1 = sectList[i+1]->surroundingRects(sf::Vector2i(0, rect.top), 
									sf::Vector2i(rect.left + rect.width - sectList[i+1]->getOffset().x, rect.top + rect.height));
						nearRects.insert(nearRects.end(), t1.begin(), t1.end());
						return nearRects;
					}
				}
			}
		}
	}
	return nearRects;
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

int Level::getLevelWidth()
{
	return levelWidth;
}