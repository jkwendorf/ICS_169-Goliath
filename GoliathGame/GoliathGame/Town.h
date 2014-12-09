#pragma once 

#include "TextureManager.h"
#include "BaseGameScreen.h"
#include "Global.h"
#include "Level.h"
#include <SFML\Audio\Music.hpp>

class Town : public BaseGameScreen
{
private:
	bool changeScreen;
	int currentlySelected;
	float testingTimer;
	sf::Sprite* background;
	sf::Sprite* highlight;
	sf::Vector2f* pointsToHighlight;
	sf::View view;
	sf::Music townMusic;

	void SetUpPoints();
public:
	Town();
	virtual ~Town();

	void ChangeSelected(bool left);
	void ClickCurrentObject();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void DeleteLevel();
	void CheckChangeScreen(BaseGameScreen*& newScreen);

};
