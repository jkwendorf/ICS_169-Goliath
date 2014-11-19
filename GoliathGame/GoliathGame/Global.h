#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <SFML/Graphics.hpp>
// JW: In the future, we might want to make Global a static class so we can alter values

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FPS 30
#define	EDITOR_TILE_WIDTH 100
#define EDITOR_TILE_HEIGHT 100
#define GAME_TILE_DIM 32
#define PLAYER_DIM 64
#define PLAYER_SPRITE_DIM 256
#define TileSheetRows 5
#define TileSheetCols 5

//ND: Offset initially set with define. Will figure out method function for proper calculation
#define X_OFFSET 100
#define Y_OFFSET 100

class Global
{
public :
	static Global& GetInstance()
	{
		static Global instance;
		return instance;
	}

	std::map<std::string, int> levelSizes;

	void ParseLevelSizes();
	bool checkPoint(const sf::Vector2i& p, const sf::IntRect& r);

	sf::Vector2f topLeft;
	int fps;
	int xOffset;
	int yOffset;

	Global();
	~Global();

	void calculateOffset(); //Calculates offset and sets it using current screen size
};