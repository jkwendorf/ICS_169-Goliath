#include "UserInterface.h"
#include "Global.h"

UserInterface::UserInterface(float h, float s)
	:showHealth1(false), showHealth2(false), showHealth3(false), showHealth4(false)
	/*:healthBar1(sf::Vector2f(100, 50)), healthBar2(sf::Vector2f(100, 50)), 
	healthBar3(sf::Vector2f(100, 50)), healthBar4(sf::Vector2f(100, 50)),
	showHealth1(true), showHealth2(true), showHealth3(true), showHealth4(true),
	staminaBar(sf::Vector2f((s * 6), 50))*/
{
	TextureManager::GetInstance().retrieveTexture("Heart1");
	TextureManager::GetInstance().retrieveTexture("Heart2");
	TextureManager::GetInstance().retrieveTexture("Heart3");
	healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart4"));
	healthIcon.setScale(0.1, 0.1);
}

UserInterface::~UserInterface()
{
	//delete healthBar;
	//delete staminaBar;
}

void UserInterface::resetUI()
{
	showHealth1 = false;
	showHealth2 = false;
	showHealth3 = false;
	showHealth4 = true;
	healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart4"));
}

void UserInterface::draw(sf::RenderWindow& window)
{
	window.draw(healthIcon);
}

void UserInterface::update(float h, float s)
{
	if(h > 75.f && !showHealth4)
	{
		showHealth4 = true;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart4"));
	}

	if(h > 50.f && h <= 75.f && !showHealth3)
	{
		showHealth3 = true;
		showHealth4 = false;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart3"));
	}

	if(h > 25.f && h <= 50.f && !showHealth2)
	{
		showHealth2 = false;
		showHealth3 = true;
		showHealth4 = false;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart2"));
	}

	if(h > 1.f && h <= 25.f && !showHealth1)
	{
		showHealth1 = true;
		showHealth2 = false;
		showHealth3 = false;
		showHealth4 = false;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart1"));
	}

	healthIcon.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 20);

	/*healthBar1.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar1.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 20);
	
	healthBar2.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar2.setPosition(Global::GetInstance().topLeft.x + 40 + 100, Global::GetInstance().topLeft.y + 20);
	
	healthBar3.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar3.setPosition(Global::GetInstance().topLeft.x + 60 + 200, Global::GetInstance().topLeft.y + 20);

	healthBar4.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar4.setPosition(Global::GetInstance().topLeft.x + 80 + 300, Global::GetInstance().topLeft.y + 20);

	staminaBar.setSize(sf::Vector2f((s * 6), 50));
	staminaBar.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 90);*/
}

void UserInterface::updateDifferent(float h, float s, sf::Vector2f offset)
{
	if(h > 75.f && !showHealth4)
	{
		showHealth4 = true;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart4"));
	}

	if(h > 50.f && h <= 75.f && !showHealth3)
	{
		showHealth3 = true;
		showHealth4 = false;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart3"));
	}

	if(h > 25.f && h <= 50.f && !showHealth2)
	{
		showHealth2 = false;
		showHealth3 = true;
		showHealth4 = false;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart2"));
	}

	if(h > 1.f && h <= 25.f && !showHealth1)
	{
		showHealth1 = true;
		showHealth2 = false;
		showHealth3 = false;
		showHealth4 = false;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart1"));
	}

	healthIcon.setPosition(Global::GetInstance().topLeft.x + 20, Global::GetInstance().topLeft.y + 20);

	/*healthBar1.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar1.setPosition(Global::GetInstance().topLeft.x + 20 + offset.x, Global::GetInstance().topLeft.y + 20 + offset.y);
	
	healthBar2.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar2.setPosition(Global::GetInstance().topLeft.x + 40 + 100 + offset.x, Global::GetInstance().topLeft.y + 20 + offset.y);
	
	healthBar3.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar3.setPosition(Global::GetInstance().topLeft.x + 60 + 200 + offset.x, Global::GetInstance().topLeft.y + 20 + offset.y);

	healthBar4.setFillColor(sf::Color(255, 0, 0, 125));
	healthBar4.setPosition(Global::GetInstance().topLeft.x + 80 + 300 + offset.x, Global::GetInstance().topLeft.y + 20 + offset.y);

	staminaBar.setSize(sf::Vector2f((s * 6), 50));
	staminaBar.setPosition(Global::GetInstance().topLeft.x + 20 + offset.x, Global::GetInstance().topLeft.y + 90 + offset.y);*/
}