#include "UserInterface.h"
#include "Global.h"

UserInterface::UserInterface(float h, float s)
	:healthBar1(sf::Vector2f(100, 50)), healthBar2(sf::Vector2f(100, 50)), 
	healthBar3(sf::Vector2f(100, 50)), healthBar4(sf::Vector2f(100, 50)),
	showHealth1(true), showHealth2(true), showHealth3(true), showHealth4(true),
	staminaBar(sf::Vector2f((s * 6), 50))
{
	healthBar1.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar1.setOutlineColor(sf::Color::Black);
	healthBar1.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 20);
	
	healthBar2.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar2.setOutlineColor(sf::Color::Black);
	healthBar2.setPosition(Global::GetInstance().topLeft.x + 40 + 100, Global::GetInstance().topLeft.y + 20);
	
	healthBar3.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar3.setOutlineColor(sf::Color::Black);
	healthBar3.setPosition(Global::GetInstance().topLeft.x + 60 + 200, Global::GetInstance().topLeft.y + 20);

	healthBar4.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar4.setOutlineColor(sf::Color::Black);
	healthBar4.setPosition(Global::GetInstance().topLeft.x + 80 + 300, Global::GetInstance().topLeft.y + 20);

	staminaBar.setFillColor(sf::Color(0,0,255, 125));
	staminaBar.setOutlineColor(sf::Color::Black);
	staminaBar.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 90);
}

UserInterface::~UserInterface()
{
	//delete healthBar;
	//delete staminaBar;
}

void UserInterface::resetUI()
{
	showHealth1 = true;
	showHealth2 = true;
	showHealth3 = true;
	showHealth4 = true;

}

void UserInterface::draw(sf::RenderWindow& window)
{
	if(showHealth1)
		window.draw(healthBar1);
	if(showHealth2)
		window.draw(healthBar2);
	if(showHealth3)
		window.draw(healthBar3);
	if(showHealth4)
		window.draw(healthBar4);
	window.draw(staminaBar);
}

void UserInterface::update(float h, float s)
{
	if(h < 76)
	{
		showHealth4 = false;
	}

	if(h < 51)
	{
		showHealth3 = false;
	}

	if(h < 26)
	{
		showHealth2 = false;
	}

	if(h < 1)
	{
		showHealth1 = false;
	}

	healthBar1.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar1.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 20);
	
	healthBar2.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar2.setPosition(Global::GetInstance().topLeft.x + 40 + 100, Global::GetInstance().topLeft.y + 20);
	
	healthBar3.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar3.setPosition(Global::GetInstance().topLeft.x + 60 + 200, Global::GetInstance().topLeft.y + 20);

	healthBar4.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar4.setPosition(Global::GetInstance().topLeft.x + 80 + 300, Global::GetInstance().topLeft.y + 20);

	staminaBar.setSize(sf::Vector2f((s * 6), 50));
	staminaBar.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 90);
}

void UserInterface::updateDifferent(float h, float s, float offset)
{
	if(h < 76)
	{
		showHealth4 = false;
	}

	if(h < 51)
	{
		showHealth3 = false;
	}

	if(h < 26)
	{
		showHealth2 = false;
	}

	if(h < 1)
	{
		showHealth1 = false;
	}

	healthBar1.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar1.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 20);
	
	healthBar2.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar2.setPosition(Global::GetInstance().topLeft.x + 40 + 100, Global::GetInstance().topLeft.y + 20);
	
	healthBar3.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar3.setPosition(Global::GetInstance().topLeft.x + 60 + 200, Global::GetInstance().topLeft.y + 20);

	healthBar4.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar4.setPosition(Global::GetInstance().topLeft.x + 80 + 300, Global::GetInstance().topLeft.y + 20);

	staminaBar.setSize(sf::Vector2f((s * 6), 50));
	staminaBar.setPosition(Global::GetInstance().topLeft.x + 20, offset + 90);
}