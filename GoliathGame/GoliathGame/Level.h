#pragma once

#include "Section.h"
#include "Player.h"
#include "Global.h"

class Level
{
private:
	Section** sectList;
	int numSect, levelNum, levelWidth;;
	sf::Vector2i firstGrid;
	sf::Vector2i firstGridDim;
	sf::Vector2i secGrid;
	sf::Vector2i secGridDim;

	Level();
	void LoadLevel();
	bool CheckSectionOnScreen(int sectionNum);
	std::vector<BaseObject*> checkBotRight(int i, sf::IntRect& rect);
	std::vector<sf::Vector2i*> inSameGrid(const sf::Vector2i& p1, const sf::Vector2i& p2);
	std::vector<sf::Vector2i*> inDifferentGrid(const sf::Vector2i& p1, const sf::Vector2i& p2, const sf::Vector2i& p3, const sf::Vector2i& p4);
	std::vector<BaseObject*> checkUpperLeftSameGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, const sf::Vector2i& botRight, bool checkBoxOnly, bool grapple = false);
	std::vector<BaseObject*> checkLowerRightNextGrid(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, const sf::Vector2i& botRight, bool checkBoxOnly, bool grapple = false);
	std::vector<BaseObject*> checkLowerRightLastCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, const sf::Vector2i& botRight);
	std::vector<BaseObject*> checkUpperLeftFirstCol(int currentGrid, sf::IntRect& rect, const sf::Vector2i& topLeft, const sf::Vector2i& botRight);
	std::vector<BaseObject*> GetNearTiles(sf::IntRect& player, bool checkBoxOnly = false, bool grapple = false);

public:
	//Player player;
	Level(int levelNumber);
	~Level();
	
	std::vector<BaseObject*> GetCollidableTiles(Player& player);
	std::vector<BaseObject*> GetInteractableTiles(Player& player);
	std::vector<BaseObject*> GetGrapplableTiles(Player& player);

	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void print();
	int getLevelWidth();
};