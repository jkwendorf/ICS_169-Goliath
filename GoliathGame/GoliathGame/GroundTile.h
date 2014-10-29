#pragma once 

#include "BaseObject.h"
#include "Global.h"

class GroundTile : public BaseObject
{
private:
	
public:
	GroundTile();
	GroundTile(int tileNum, sf::Vector2i pos, int screenRows, int screenCols, sf::Texture* texture);
	~GroundTile();
	sf::Sprite getSprite();
	void draw(sf::RenderWindow& window);
};
