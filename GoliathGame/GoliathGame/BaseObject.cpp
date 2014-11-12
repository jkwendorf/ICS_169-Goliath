
#include "BaseObject.h"

BaseObject::BaseObject()
	:collidable(false), isFalling(false), objectNum(-999), testingNum(-1)
{

}

BaseObject::BaseObject(bool canCollide)
	:collidable(canCollide), isFalling(false), objectNum(-999)
{
	
}

BaseObject::BaseObject(int testing, int objectNum, const sf::Vector2i& pos, const sf::Vector2i& sectionOffSet, float scale, sf::Texture* texture, bool canCollide)
	:collidable(canCollide), isFalling(false), objectNum(objectNum), testingNum(testing)
{
	sprite.setTexture(*texture);
	sf::IntRect temp = sf::IntRect(EDITOR_TILE_HEIGHT * (objectNum % TileSheetRows),
				EDITOR_TILE_WIDTH * (objectNum / TileSheetRows),EDITOR_TILE_WIDTH, EDITOR_TILE_HEIGHT);
	//std::cout << "Pos x: " <<  temp.left << ". Pos Y: " << temp.top << std::endl;
	sprite.setTextureRect(temp);
	//std::cout << "Pos x: " <<  pos.x << ". Pos Y: " << pos.y << std::endl;
	sprite.setPosition(pos.x + sectionOffSet.x, pos.y + sectionOffSet.y);
	sprite.setScale(scale, scale);
	//std::cout << "Scale x: " <<  sprite.getScale().x << ". Scale Y: " << sprite.getScale().y << std::endl;
}

BaseObject::~BaseObject()
{

}

void BaseObject::update(float deltaTime)
{

}

void BaseObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void BaseObject::print()
{
	std::cout << "(" << testingNum << ")";
}