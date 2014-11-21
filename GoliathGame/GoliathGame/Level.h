#pragma once

#include "Section.h"
#include "Player.h"
#include "Global.h"

class Level
{
private:
	Section** sectList;
	int numSect, levelNum, levelWidth;
	bool loadedTitles;

	Level();
	void LoadLevel();
	bool CheckSectionOnScreen(int sectionNum);
	std::vector<Tile*> checkBotRight(int i, sf::IntRect& rect);
	std::vector<sf::Vector2i*> inSameGrid(const sf::Vector2i& p1, const sf::Vector2i& p2);
	std::vector<sf::Vector2i*> inDifferentGrid(const sf::Vector2i& p1, const sf::Vector2i& p2, const sf::Vector2i& p3, const sf::Vector2i& p4);
	void checkUpperLeftSameGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
		const sf::Vector2i& botRight, std::vector<Tile*>& nearTiles, bool checkBoxOnly, bool grapple = false);
	void checkLowerRightNextGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, 
		const sf::Vector2i& botRight, std::vector<Tile*>& nearTiles, bool checkBoxOnly, bool grapple = false);
	void checkLowerRightLastCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, const sf::Vector2i& botRight,
		std::vector<Tile*>& nearTiles);
	void checkUpperLeftFirstCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, const sf::Vector2i& botRight,
		std::vector<Tile*>& nearTiles);
	void GetNearTiles(sf::IntRect& player, std::vector<Tile*>& nearTiles, bool checkBoxOnly = false, bool grapple = false);

public:
	//Player player;
	Level(int levelNumber);
	~Level();
	
	void GetCollidableTiles(Player& player, std::vector<Tile*>& nearTiles);
	bool NearInteractableTiles(Player& player, std::vector<Tile*>& nearTiles);
	void GetGrapplableTiles(Player& player, std::vector<Tile*>& nearTiles);

	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void print();
	int getLevelWidth();
};