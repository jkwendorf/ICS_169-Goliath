#pragma once

#include "Global.h"
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
	
	GroundTile* tiles;

	bool CheckNear(int tileNum, sf::Vector2f pos);
	void LoadTileMap();
	void Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters = " ");

public:
	Section();
	Section(std::string s, sf::Vector2i sectionOffSet);
	~Section();
	int getSectionWidth();
	int getSectionHeight();
	bool inWindow();
	std::vector<GroundTile> Section::GetNearTiles(sf::Vector2f pos);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
};