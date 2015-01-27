#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FPS 60
#define	EDITOR_TILE_WIDTH 100
#define EDITOR_TILE_HEIGHT 100
#define GAME_TILE_DIM 64
#define PLAYER_DIM 48
#define PLAYER_DIM_X 48
#define PLAYER_DIM_Y PLAYER_DIM_X * 2
#define ENEMY_ATTACK_LOW_THRESHOLD 100
#define ENEMY_ATTACK_HIGH_THRESHOLD 400

//Player sprite dim never used...
#define PLAYER_SPRITE_DIM 1000

#define TileSheetRows 4
#define TileSheetCols 5

//ND: Offset initially set with define. Will figure out method function for proper calculation
#define X_OFFSET 100
#define Y_OFFSET 100

typedef unsigned __int8	uint8;
