#pragma once

#include <fstream>
#include "GroundTile.h"
#include "TextureManager.h"

class Screen 
{
private:
	int screenNum;
	int width, height;
	int tileOffSetX, tileOffSetY;
	int numOfTiles;
	std::string pathToText;
	
	GroundTile* tiles;

	Screen();
	void LoadTileMap();
	void Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters = " ");

public:
	Screen(std::string s);
	~Screen();
	int getScreenWidth();
	int getScreenHeight();
	bool inWindow(int offSetX, int offSetY);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
};