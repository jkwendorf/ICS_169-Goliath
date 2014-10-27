#include "BaseObject.h"

void BaseObject::draw(sf::Texture* text, int x, int y)
{
	//Sets the sprite to have a texture
	//Sets the sprite at a location on the window
	sprite.setTexture(*text);
	sprite.setPosition(x, y);
}