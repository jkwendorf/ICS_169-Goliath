#pragma once

#include "Section.h"

class Level
{
private:
	Section* sectionList;
	int levelNum;
	int numSections;
	Level();
	void LoadLevel();
	bool CheckSectionOnScreen(int sectionNum);
public:
	Level(int levelNumber, int numOfSections);
	~Level();
	std::vector<BaseObject> Level::GetNearTiles(const sf::Vector2f& pos);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);


};