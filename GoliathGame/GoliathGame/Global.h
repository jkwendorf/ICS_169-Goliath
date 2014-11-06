#pragma once

#include <iostream>
// JW: In the future, we might want to make Global a static class so we can alter values

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 30
#define	EDITOR_TILE_WIDTH 100
#define EDITOR_TILE_HEIGHT 100
#define GAME_TILE_WIDTH 50
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

	void setScreenSize(int w, int h);
	void setFPS(int f);

	int x;
	int y;
	int fps;
	int xOffset;
	int yOffset;

	Global();
	~Global();

private:
	void calculateOffset(); //Calculates offset and sets it using current screen size
};