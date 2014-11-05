
#include "BaseObject.h"

BaseObject::BaseObject()
	:collidable(false)
{

}

BaseObject::BaseObject(bool canCollide)
	:collidable(canCollide)
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