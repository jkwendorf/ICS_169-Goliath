#pragma once

#include "Section.h"
#include "Player.h"
#include "Global.h"

class Room
{
private:
	Section** sectList;
	int numSect, roomNum, roomWidth, roomHeight;
	bool loadedTitles;
	sf::Vector2f startPos;

	Room();
	void LoadRoom(int levelNumber);
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
	Room(int levelNumber, int roomNumber);
	~Room();
	
	void GetCollidableTiles(BaseObject& obj, std::vector<Tile*>& nearTiles);
	bool NearInteractableTiles(BaseObject& obj);
	void GetGrapplableTiles(Player& player, std::vector<Tile*>& nearTiles);

	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void print();
	int getRoomNumber();
	int getroomWidth();
	int getroomHeight();
	sf::Vector2f getStartPos();
};