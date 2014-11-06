#pragma once 

#include "BaseObject.h"
#include "Global.h"

class GroundTile : public BaseObject
{
private:
	sf::Vector2i offSet;
public:
	GroundTile();
	GroundTile(int tileNum, const sf::Vector2i& pos, const sf::Vector2i& screenOffSet, const sf::Vector2f& scale, sf::Texture* texture);
	~GroundTile();
	void SetOffSet(int offSetX, int offSetY);
	void draw(sf::RenderWindow& window);
};
