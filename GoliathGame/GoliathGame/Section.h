#pragma once

#include "BaseObject.h"
#include "Global.h"
#include <fstream>
#include "TextureManager.h"
#include <vector>
#include "Tile.h"
#include "Enemy.h"

class Section 
{
private:
	int sectionNum, numOfTiles;
	int ** grid1;
	
	sf::Vector2i gDim, offset;
	sf::Vector2f startPos;
	std::string pathToText;

	Section();
	void LoadTileMap(std::vector<Enemy*> &enemyList);
	void Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters = " ");
public:
	Section(int sectionNumber, std::string& s, sf::Vector2i& offset, std::vector<Enemy*> &enemyList);
	~Section();
	sf::Vector2i getOffset();
	sf::Vector2i getGridDim();
	int getWidth();
	int getHeight();
	int getGridNum();
	sf::Vector2f getStartPos();

	bool inWindow();
	bool checkPlayerInGrid(const BaseObject& player);

	std::vector<sf::Vector2i*> getIntersectPoints(const BaseObject& rect);
	std::vector<sf::Vector2i*> getIntersectPoints(const sf::Vector2i& p1, const sf::Vector2i& p2);
	void surroundingRects(const sf::Vector2i& p1, const sf::Vector2i& p2, std::vector<Tile*>& nearTiles,
		bool checkHorz = true, bool checkVert = true);
	void checkGrapple(const sf::Vector2i& p1, const sf::Vector2i& p2, std::vector<Tile*>& nearTiles);
	void checkInteractable(const sf::Vector2i& p1, const sf::Vector2i& p2, std::vector<Tile*>& nearTiles);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void print();

};