#pragma once

#include <fstream>
#include "GroundTile.h"
#include "TextureManager.h"

class Section 
{
private:
	int screenNum;
	int width, height;
	sf::Vector2i sOffSet;
	int numOfTiles;
	std::string pathToText;
	
	BaseObject * tiles;

	bool CheckNear(int tileNum, const sf::Vector2f& pos);
	void LoadTileMap();
	void Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters = " ");

public:
	Section();
	Section(std::string& s, const sf::Vector2i& sectionOffSet);
	~Section();
	int getSectionWidth();
	int getSectionHeight();
	bool inWindow();
	std::vector<BaseObject> Section::GetNearTiles(const sf::Vector2f& pos);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
};