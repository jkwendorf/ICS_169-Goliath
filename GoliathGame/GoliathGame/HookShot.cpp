#include "HookShot.h"

HookShot::HookShot()
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));
	sprite.setScale(0.05,0.05);
}

HookShot::~HookShot()
{

}

void HookShot::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void HookShot::update(float deltaTime)
{

}

void HookShot::attack()
{

}

void HookShot::grappleToLocation(sf::Vector2f location)
{
	sprite.move(location);
}