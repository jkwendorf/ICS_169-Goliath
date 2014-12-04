#pragma once 

#include "TextureManager.h"
#include "BaseGameScreen.h"
#include "Global.h"

class Town : public BaseGameScreen
{
private:
	bool changeScreen;
	int currentlySelected;
	sf::Sprite* background;
	sf::Sprite* highlight;
	sf::Vector2f pointsToHighlight[5];

	void SetUpPoints();
public:
	Town();
	~Town();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void DeleteLevel();
	bool CheckChangeScreen();

};
