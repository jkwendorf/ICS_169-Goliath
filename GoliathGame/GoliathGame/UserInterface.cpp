#include "UserInterface.h"
#include "Global.h"

UserInterface::UserInterface(float h, float s, int numTreasure)
	:showHealth1(false), showHealth2(false), showHealth3(false), showHealth4(false), drawPlease(true), totalTreasure(numTreasure),
	collectedTreasure(0)
	/*:healthBar1(sf::Vector2f(100, 50)), healthBar2(sf::Vector2f(100, 50)), 
	healthBar3(sf::Vector2f(100, 50)), healthBar4(sf::Vector2f(100, 50)),
	showHealth1(true), showHealth2(true), showHealth3(true), showHealth4(true),
	staminaBar(sf::Vector2f((s * 6), 50))*/
{
	TextureManager::GetInstance().retrieveTexture("Heart1");
	TextureManager::GetInstance().retrieveTexture("Heart2");
	TextureManager::GetInstance().retrieveTexture("Heart3");
	healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart4"));
	healthIcon.setScale(0.13, 0.13);
	treasure = sf::Text(std::to_string(collectedTreasure) + " / " + std::to_string(totalTreasure), Global::GetInstance().font);
	addSounds();
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
	drawPlease = true;
}

void UserInterface::draw(sf::RenderWindow& window)
{
	if(drawPlease)
	{
		window.draw(healthIcon);
	}
	if (totalTreasure > 0)
		window.draw(treasure);
}

void UserInterface::flashHealth()
{
	drawPlease = !drawPlease;
}

void UserInterface::addSounds()
{
	uiSounds[0] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("FoundAll1")));
	uiSounds[1] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("FoundAll2")));
	uiSounds[2] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("FoundAll3")));
}

void UserInterface::endFlash()
{
	drawPlease = true;
}

void UserInterface::update(float h, float s, sf::Vector2f offset)
{
	treasure.setString(std::to_string(collectedTreasure) + " / " + std::to_string(totalTreasure));
	if(h > 75.f && !showHealth4)
	{
		showHealth1 = false;
		showHealth2 = false;
		showHealth3 = false;
		showHealth4 = true;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart4"));
	}

	if(h > 50.f && h <= 75.f && !showHealth3)
	{
		showHealth1 = false;
		showHealth2 = false;
		showHealth3 = true;
		showHealth4 = false;
		healthIcon.setTexture(*TextureManager::GetInstance().retrieveTexture("Heart3"));
	}

	if(h > 25.f && h <= 50.f && !showHealth2)
	{
		showHealth1 = false;
		showHealth2 = true;
		showHealth3 = false;
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

	healthIcon.setPosition(Global::GetInstance().topLeft.x + 20 + offset.x, Global::GetInstance().topLeft.y + 20 + offset.y);
	if (totalTreasure > 0)
		treasure.setPosition(Global::GetInstance().topLeft.x + healthIcon.getGlobalBounds().width + 20 + offset.x, Global::GetInstance().topLeft.y + 20 + offset.y);

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

void UserInterface::depleteHealth()
{
	showHealth1 = false;
	showHealth2 = false;
	showHealth3 = false;
	showHealth4 = false;
	drawPlease = false;
}
	
void UserInterface::update(float h, float s)
{
	update(h, s, sf::Vector2f(0, 0));
}


void UserInterface::addTreasure()
{
	collectedTreasure++;
	if(collectedTreasure == totalTreasure)
	{
		int x = rand() % 3;
		uiSounds[x].play();
	}
}

bool UserInterface::collectedAllTreasure()
{
	return collectedTreasure == totalTreasure;
}