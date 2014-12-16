#include "UserInterface.h"
#include "Global.h"

UserInterface::UserInterface(float h, float s)
	:healthBar(sf::Vector2f((h * 6), 50)), staminaBar(sf::Vector2f((s * 6), 50))
{
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setOutlineColor(sf::Color::Black);
	healthBar.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 20);

	staminaBar.setFillColor(sf::Color::Blue);
	staminaBar.setOutlineColor(sf::Color::Black);
	staminaBar.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 90);
}

UserInterface::~UserInterface()
{
	//delete healthBar;
	//delete staminaBar;
}

void UserInterface::draw(sf::RenderWindow& window)
{
	window.draw(healthBar);
	window.draw(staminaBar);
}

void UserInterface::update(float h, float s)
{
	healthBar.setSize(sf::Vector2f((h * 6), 50));
	healthBar.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 20);

	staminaBar.setSize(sf::Vector2f((s * 6), 50));
	staminaBar.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 90);
}

void UserInterface::updateDifferent(float h, float s, float offset)
{
	healthBar.setSize(sf::Vector2f((h * 6), 50));
	healthBar.setPosition(Global::GetInstance().topLeft.x + 20, offset + 20);

	staminaBar.setSize(sf::Vector2f((s * 6), 50));
	staminaBar.setPosition(Global::GetInstance().topLeft.x + 20, offset + 90);
}