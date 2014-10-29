#pragma once 

#include "BaseObject.h"
#include "Global.h"

class GroundTile : public BaseObject
{
private:
	GroundTile();
public:
	GroundTile(int tileNum, sf::Vector2i pos, int tileSheetRows, int tileSheetCols, sf::Texture* texture);
	~GroundTile();
	sf::Sprite getSprite();
	void draw(sf::RenderWindow& window);
};
