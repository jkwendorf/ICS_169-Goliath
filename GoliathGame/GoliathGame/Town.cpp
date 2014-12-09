#include "Town.h"

Town::Town()
	:changeScreen(false), currentlySelected(0), 
	highlight(new sf::Sprite(*TextureManager::GetInstance().retrieveTexture("HighLight"))),
	background(new sf::Sprite(*TextureManager::GetInstance().retrieveTexture("Town"))),
	pointsToHighlight(new sf::Vector2f[5]),
	testingTimer(20.0)
{
	SetUpPoints();
	highlight->scale((float)(32) / highlight->getTexture()->getSize().x, (float)(32) / highlight->getTexture()->getSize().y);

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	if (!townMusic.openFromFile("media/sound/SilverScrapes.wav"))
	{
		std::cout << "Error for loading file" << std::endl;
	}
	townMusic.setLoop(true);
	townMusic.play();
}

Town::~Town()
{
	DeleteLevel();
}

void Town::SetUpPoints()
{
	pointsToHighlight[0] = sf::Vector2f(100,375);
	pointsToHighlight[1] = sf::Vector2f(450,585);
	pointsToHighlight[2] = sf::Vector2f(625,300);
	pointsToHighlight[3] = sf::Vector2f(1000,180);
	pointsToHighlight[4] = sf::Vector2f(1130,360);
}

void Town::ChangeSelected(bool left)
{
	if(left)
	{
		if(currentlySelected > 0)
			currentlySelected--;
		else
			currentlySelected = 5;
	}
	else
	{
		if (currentlySelected < 5)
			currentlySelected++;
		else
			currentlySelected = 0;
	}
}

void Town::ClickCurrentObject()
{
	changeScreen = true;
}

void Town::update(float deltaTime)
{
	highlight->setPosition(pointsToHighlight[currentlySelected]);
	//This is only for testing will be taken out for the game
	testingTimer -= deltaTime;
	if(testingTimer <= 0.0)
	{
		changeScreen = true;
	}
}

void Town::draw(sf::RenderWindow& window)
{
	window.draw(*background);
	window.draw(*highlight);
	window.setView(view);
}

void Town::DeleteLevel()
{
	townMusic.stop();
	delete background;
	delete highlight;
	delete[] pointsToHighlight;
}

void Town::CheckChangeScreen(BaseGameScreen*& newScreen)
{
	if(changeScreen)
	{
		newScreen = new Level(1);
	}
}