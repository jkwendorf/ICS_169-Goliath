#include "HookShot.h"
#include "Utility.h"

HookShot::HookShot() : 
	hookedOnSomething(false), grappleInProgress(false), fireRight(false), isDisabled(false), grappleLength(400), 
	hitNonGrappleTile(true), hookshotSpeed(10)
{
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("Grapple"));
	sprite.setScale(0.025,0.025);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	currentCooldown = 0.0;
	weaponCooldown = 2.0;
	grappleBox = grappleLength/sqrt(2);
	for(int x = 0; x < 10; x++)
	{
		hookshotChain[x].setTexture(*TextureManager::GetInstance().retrieveTexture("rock"));
		hookshotChain[x].setOrigin(hookshotChain[x].getLocalBounds().width/2, hookshotChain[x].getLocalBounds().height/2);
	}
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
		sprite.move((grappleLocation.x - sprite.getPosition().x)*hookshotSpeed*deltaTime, 
			(grappleLocation.y - sprite.getPosition().y)*hookshotSpeed*deltaTime);	
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

void HookShot::updateChain(sf::Vector2f playerPos)
{
	sf::Vector2f normalDirectionTowardHookshot = sprite.getPosition() - playerPos;
	normalize(normalDirectionTowardHookshot);
	sf::Vector2f directionTowardHookshot = sprite.getPosition() - playerPos;
	//if(grappleInProgress || hookedOnSomething)
		for(int x = 0; x < 10; x++)
			hookshotChain[x].setPosition(playerPos
			+ sf::Vector2f(directionTowardHookshot.x * x / 10, directionTowardHookshot.y * x /10));
}