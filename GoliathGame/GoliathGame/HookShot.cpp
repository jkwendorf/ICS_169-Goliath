#include "HookShot.h"

HookShot::HookShot() : 
	hookedOnSomething(false), grappleInProgress(false), fireRight(false), isDisabled(false), grappleLength(400)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));
	sprite.setScale(0.05,0.05);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	currentCooldown = 0.0;
	weaponCooldown = 1.0;
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
	if(grappleInProgress)
	{
		currentCooldown += deltaTime;
		if(currentCooldown > weaponCooldown)
		{
			currentCooldown = 0.0;
			grappleInProgress = false;
		}
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