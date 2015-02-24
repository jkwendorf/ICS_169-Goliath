#pragma once

#include "BaseObject.h"
#include "Global.h"
#include <fstream>
#include "TextureManager.h"
#include <vector>
#include <list>
#include <memory>
#include "Tile.h"
#include "Enemy.h"

class Section 
{
private:
	int sectionNum, numOfTiles;
	Tile** grid1;
	Global global;
	sf::Vector2i gDim;
	sf::Vector2f startPos, offset;
	std::string pathToText;

	Section();
	void LoadTileMap(std::vector<std::shared_ptr<Enemy>> &enemyList, std::vector<Tile*> &arrowTileList, std::list<Tile*> &destructTileList, std::list<Tile*> &hitPointTileList);
	void Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters = " ");
	bool checkToRender(int tileNum);
public:
	Section(int sectionNumber, std::string& s, sf::Vector2f& offset, std::vector<std::shared_ptr<Enemy>> &enemyList, std::vector<Tile*> &arrowTileList, std::list<Tile*> &destructTileList, std::list<Tile*> &hitPointTileList);
	~Section();
	sf::Vector2f getOffset();
	sf::Vector2i getGridDim();
	int getWidth();
	int getHeight();
	int getGridNum();
	sf::Vector2f getStartPos();

	bool inWindow();
	bool checkPlayerInGrid(const BaseObject& player);

	std::vector<sf::Vector2f> getIntersectPoints(const BaseObject& rect);
	std::vector<sf::Vector2f> getIntersectPoints(const sf::Vector2f& p1, const sf::Vector2f& p2);
	void surroundingRects(const sf::Vector2f& p1, const sf::Vector2f& p2, std::vector<Tile*>& nearTiles,
		bool checkHorz = true, bool checkVert = true);
	void checkGrapple(const sf::Vector2f& p1, const sf::Vector2f& p2, std::vector<Tile*>& nearTiles);
	void checkInteractable(const sf::Vector2f& p1, const sf::Vector2f& p2, std::vector<Tile*>& nearTiles);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void print();

};