#include "Town.h"

Town::Town()
	:changeScreen(false), currentlySelected(0), 
	highlight(new sf::Sprite(*TextureManager::GetInstance().retrieveTexture("HighLight"))),
	background(new sf::Sprite(*TextureManager::GetInstance().retrieveTexture("Town")))
{
	SetUpPoints();
}

Town::~Town()
{

}

void Town::SetUpPoints()
{
	pointsToHighlight[0] = sf::Vector2f(100,375);
	pointsToHighlight[1] = sf::Vector2f(450,585);
	pointsToHighlight[2] = sf::Vector2f(625,300);
	pointsToHighlight[3] = sf::Vector2f(1000,180);
	pointsToHighlight[4] = sf::Vector2f(1130,360);
}

void Town::update(float deltaTime)
{
	highlight->setPosition(pointsToHighlight[currentlySelected]);
}

void Town::draw(sf::RenderWindow& window)
{
	window.draw(*background);
	window.draw(*highlight);
}

void Town::DeleteLevel()
{
	delete background;
	delete highlight;
}

bool Town::CheckChangeScreen()
{
	return changeScreen;
}