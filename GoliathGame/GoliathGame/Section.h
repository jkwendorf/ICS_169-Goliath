#pragma once

#include "BaseObject.h"
#include "Global.h"
#include <fstream>
#include "TextureManager.h"
#include <vector>

class Section 
{
private:
	int sectionNum, numOfTiles;
	BaseObject** grid;
	
	sf::Vector2i gDim, offset;
	std::string pathToText;

	Section();
	void LoadTileMap();
	void Tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters = " ");
public:
	Section(int sectionNumber, std::string& s, const sf::Vector2i& offset);
	~Section();
	sf::Vector2i getOffset();
	sf::Vector2i getGridDim();
	int getWidth();
	int getHeight();
	int getGridNum();
	bool inWindow();
	bool checkPlayerInGrid(const BaseObject& player);
	std::vector<sf::Vector2i*> getIntersectPoints(const BaseObject& rect);
	std::vector<sf::Vector2i*> getIntersectPoints(const sf::Vector2i& p1, const sf::Vector2i& p2);
	void surroundingRects(const sf::Vector2i& p1, const sf::Vector2i& p2, std::vector<BaseObject*>& nearTiles,
		bool checkHorz = true, bool checkVert = true);
	void checkGrapple(const sf::Vector2i& p1, const sf::Vector2i& p2, std::vector<BaseObject*>& nearTiles);
	void update(float deltaTime);
	void draw(sf::RenderWindow& w);
	void print();

};