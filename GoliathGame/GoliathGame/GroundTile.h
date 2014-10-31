#pragma once 

#include "BaseObject.h"
#include "Global.h"

class GroundTile : public BaseObject
{
private:
	sf::Vector2i offSet;
public:
	GroundTile();
	GroundTile(int tileNum, sf::Vector2i pos, sf::Vector2i screenOffSet, sf::Vector2f scale, sf::Texture* texture);
	~GroundTile();
	void SetOffSet(int offSetX, int offSetY);
	sf::Sprite getSprite();
	void draw(sf::RenderWindow& window);
};
