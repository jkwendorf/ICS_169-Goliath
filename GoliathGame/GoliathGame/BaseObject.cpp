
#include "BaseObject.h"

BaseObject::BaseObject()
	:collidable(false), isFalling(false), objectNum(-999), testingNum(-1), grappleable(false), interactable(false)
{
}

BaseObject::BaseObject(bool canCollide)
	:collidable(canCollide), isFalling(false), objectNum(-999), grappleable(false), interactable(false)
{
}

BaseObject::BaseObject(int objectNum_)
	:objectNum(objectNum_), collidable(false), isFalling(false), testingNum(-1), grappleable(false), interactable(false)
{
}

BaseObject::BaseObject(int testing, int objectNum, const sf::Vector2i& pos, const sf::Vector2i& sectionOffSet, float scale, sf::Texture* texture, bool canCollide,  bool grappleable, bool interactable)
	:collidable(canCollide), isFalling(false), objectNum(objectNum), testingNum(testing), grappleable(grappleable), interactable(interactable)
{
	sprite.setTexture(*texture);
	sf::IntRect temp = sf::IntRect(EDITOR_TILE_WIDTH * (objectNum % TileSheetCols),
				EDITOR_TILE_HEIGHT * (objectNum / TileSheetCols),EDITOR_TILE_WIDTH, EDITOR_TILE_HEIGHT);

	sprite.setTextureRect(temp);

	sprite.setPosition(pos.x + sectionOffSet.x, pos.y + sectionOffSet.y);
	sprite.setScale(scale, scale);

	hitbox.setPosition(pos.x + sectionOffSet.x, pos.y + sectionOffSet.y);
	hitbox.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	hitbox.setFillColor(sf::Color::Blue);
}

BaseObject::~BaseObject()
{

}

void BaseObject::update(float deltaTime)
{
	hitbox.setPosition(sprite.getPosition());
}

void BaseObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	//window.draw(hitbox);
}

void BaseObject::print()
{
	std::cout << "(" << objectNum << ")";
}