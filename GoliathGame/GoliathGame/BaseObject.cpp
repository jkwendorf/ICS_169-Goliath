
#include "BaseObject.h"

BaseObject::BaseObject()
	:collidable(false), isFalling(false)
{

}

BaseObject::BaseObject(bool canCollide)
	:collidable(canCollide), isFalling(false)
{

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