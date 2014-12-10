#include "HookShot.h"

HookShot::HookShot() : 
	hookedOnSomething(false), grappleInProgress(false), fireRight(false), grappleLength(320)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));
	sprite.setScale(0.05,0.05);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
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
	if(!hookedOnSomething)
	{
		sprite.move((grappleLocation.x - sprite.getPosition().x)*5*deltaTime, (grappleLocation.y - sprite.getPosition().y)*5*deltaTime);
		
	}
	//else
	//	grappleLocation = sprite.getPosition();
}

void HookShot::update(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void HookShot::attack()
{

}

void HookShot::grappleToLocation(sf::Vector2f location)
{
	grappleLocation = location;
}