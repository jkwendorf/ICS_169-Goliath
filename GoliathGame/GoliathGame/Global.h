#pragma once

#include "pugixml.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include "PlayerInventory.h"
// JW: In the future, we might want to make Global a static class so we can alter values


class Global
{
public :
	static Global& GetInstance()
	{
		static Global instance;
		return instance;
	}

	std::map<std::string, int> levelSizes;
	std::map<std::string, int> roomSizes;
	std::map<std::string, std::string> roomTileSheets;

	std::map<std::string, std::vector<float>> augments;
	float basePlayerStats[6];
	int enemyAttributes[4];
	int playerAttributes[6];
	PlayerInventory* inventory;

	void LoadEnemyAttributes();
	void LoadPlayerAttribtues();
	void SavePlayer();
	void ParseXML();
	void ParseLevelSizes(std::map<std::string, int>& mapToUpdate, std::string& fileName);
	void ParseLevelTileSheets();
	bool checkPoint(const sf::Vector2f& p, const sf::FloatRect& r);

	sf::Vector2f topLeft;
	int fps;
	int xOffset;
	int yOffset;
	sf::Sprite* currentTileSheet[TileSheetRows * TileSheetCols];

	Global();
	~Global();
	void CleanUp();

	void calculateOffset(); //Calculates offset and sets it using current screen size
	void SetUpTileSheet(sf::Texture* texture);

	sf::Sound test;

	
	sf::RectangleShape testingRect;
};