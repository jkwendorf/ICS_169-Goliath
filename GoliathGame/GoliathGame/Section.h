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
	
	GroundTile* tiles;

	Section();
	void LoadTileMap();
	void Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters = " ");

public:
	Section(std::string s, sf::Vector2i sectionOffSet);
	~Section();
	int getScreenWidth();
	int getScreenHeight();
	bool inWindow(int offSetX, int offSetY);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
};