
#include "Level.h"

Level::Level(int levelNumber, int numOfSections)
	:levelNum(levelNumber), numSections(numOfSections)
{
	LoadLevel();
}

Level::~Level()
{
	delete[] sectionList;
}

Level::Level()
{}
	
void Level::LoadLevel()
{
	sectionList = new Section[numSections];
	for (int i = 0; i < numSections; i++)
	{
		std::string temp = "level" + std::to_string(levelNum) + "num" + std::to_string(i);
		if(i==0)
			sectionList[i] = Section(temp, sf::Vector2i(0,0));
		else
			sectionList[i] = Section(temp, sf::Vector2i(sectionList[i-1].getSectionWidth(), 0));
	}
}

bool Level::CheckSectionOnScreen(int sectionNum)
{
	return sectionList[sectionNum].inWindow();
}

std::vector<GroundTile> Level::GetNearTiles(sf::Vector2f pos)
{
	bool lastChecked;
	std::vector<GroundTile> final;
	for (int i = 0; i < numSections; i++)
	{
		if(CheckSectionOnScreen(i))
		{
			std::vector<GroundTile> temp = sectionList[i].GetNearTiles(pos);
			final.insert(final.end(), temp.begin(), temp.end());
		}
	}
	return final;
}

void Level::update(float deltaTime)
{
	for(int i = 0; i < numSections; i++)
	{
		sectionList[i].update(deltaTime);
	}
}

void Level::draw(sf::RenderWindow& w)
{
	for(int i = 0; i < numSections; i++)
	{
		sectionList[i].draw(w);
	}
}