
#include "BaseObject.h"

BaseObject::BaseObject()
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