#include "Sword.h"

Sword::Sword():attacking(false)
{
	hitBox.setSize(sf::Vector2f(50,100));
	hitBox.setFillColor(sf::Color::Red);
	currentCooldown = 0.0;
	weaponCooldown = .5;
}

Sword::~Sword()
{

}

void Sword::update(float deltaTime)
{
	if(attacking)
	{
		currentCooldown += deltaTime;
		if(currentCooldown > weaponCooldown)
		{
			attacking = false;
			currentCooldown = 0.0;
		}
	}
}

void Sword::draw(sf::RenderWindow& window)
{
	if(currentCooldown <= weaponCooldown && attacking)
		window.draw(hitBox);
}

void Sword::attack()
{

}