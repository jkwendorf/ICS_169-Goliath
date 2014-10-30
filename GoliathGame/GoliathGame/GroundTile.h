#pragma once 

#include "BaseObject.h"
#include "Global.h"

class GroundTile : public BaseObject
{
private:
	int offSetX, offSetY;
public:
	GroundTile();
	GroundTile(int tileNum, sf::Vector2i pos, sf::Vector2i scale, sf::Texture* texture);
	~GroundTile();
	void SetOffSet(int offSetX, int offSetY);
	sf::Sprite getSprite();
	void draw(sf::RenderWindow& window);
};
