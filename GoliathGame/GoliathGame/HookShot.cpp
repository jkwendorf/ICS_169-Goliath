#include "HookShot.h"

HookShot::HookShot() : 
	hookedOnSomething(false), grappleInProgress(false), fireRight(false), isDisabled(false), grappleLength(400), hitNonGrappleTile(true)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));
	sprite.setScale(0.05,0.05);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	currentCooldown = 0.0;
	weaponCooldown = 1.0;
	grappleBox = grappleLength/sqrt(2);
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
	//std::cout << currentCooldown << " not hooked on something " << std::endl;


	if(!hookedOnSomething)
	{
		sprite.move((grappleLocation.x - sprite.getPosition().x)*5*deltaTime, (grappleLocation.y - sprite.getPosition().y)*5*deltaTime);	
	}
	else
		currentCooldown = 0.0;
	if(grappleInProgress)
	{
		currentCooldown += deltaTime;

		//std::cout << "Grapple cooldown: " << currentCooldown << std::endl;
		if(currentCooldown > weaponCooldown || hitNonGrappleTile)
		{
			currentCooldown = 0.0;
			grappleInProgress = false;
		}
	}
	//std::cout << hookedOnSomething << " " << grappleInProgress << std::endl;
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