#pragma once

#include "Section.h"
#include "Player.h"
#include "Global.h"
#include "Enemy.h"
#include "Background.h"
#include <memory>
#include <SFML\Audio\Music.hpp>

class Room
{
private:
	Section** sectList;
	int numSect, roomNum, roomWidth, roomHeight;
	bool loadedTitles;
	Global g;
	
	sf::Vector2f startPos;
	sf::Music roomMusic;

	Room();
	void LoadRoom(int levelNumber, std::vector<std::shared_ptr<Enemy>> &enemyList, std::vector<Tile*> &arrowTileList, std::list<Tile*> &destructTileList, std::list<Tile*> &hitPointTileList);
	bool CheckSectionOnScreen(int sectionNum);
	std::vector<Tile*> checkBotRight(int i, sf::FloatRect& rect);
	std::vector<sf::Vector2f> inSameGrid(const sf::Vector2f& p1, const sf::Vector2f& p2);
	std::vector<sf::Vector2f> inDifferentGrid(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4);
	void checkUpperLeftSameGrid(int currentGrid, sf::FloatRect& rect, const sf::Vector2f& topLeft, 
		const sf::Vector2f& botRight, std::vector<Tile*>& nearTiles, bool checkBoxOnly, bool grapple = false);

	void checkLowerRightNextGrid(int currentGrid, sf::FloatRect& rect, const sf::Vector2f& topLeft, 
		const sf::Vector2f& botRight, std::vector<Tile*>& nearTiles, bool checkBoxOnly, bool grapple = false);

	void checkLowerRightLastCol(int currentGrid, sf::FloatRect& rect, const sf::Vector2f& topLeft, const sf::Vector2f& botRight,
		std::vector<Tile*>& nearTiles);

	void checkUpperLeftFirstCol(int currentGrid, sf::FloatRect& rect, const sf::Vector2f& topLeft, const sf::Vector2f& botRight,
		std::vector<Tile*>& nearTiles);

	void GetNearTiles(sf::FloatRect& player, std::vector<Tile*>& nearTiles, bool checkBoxOnly = false, bool grapple = false);
	float mViewPosX;
public:
	Background bg;
	int numTreasures;
	//Player player;
	Room(int levelNumber, int roomNumber, std::vector<std::shared_ptr<Enemy>> &enemyList, std::vector<Tile*> &arrowTileList, std::list<Tile*> &destructTileList, std::list<Tile*> &hitPointTileList);
	~Room();
	
	void GetCollidableTiles(BaseObject& obj, std::vector<Tile*>& nearTiles, bool player=false);
	//These two functions only works for player 
	int NearInteractableTiles(BaseObject& obj);
	void GetGrapplableTiles(Player& player, std::vector<Tile*>& nearTiles);

	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void print();
	int getRoomNumber();
	int getroomWidth();
	int getroomHeight();
	void setViewPosition(float viewPosX);
	sf::Vector2f getStartPos();
};