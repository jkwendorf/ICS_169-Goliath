#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class UserInterface
{
public:
	UserInterface(float h, float s, int numTreasure);
	~UserInterface();

	void resetUI();
	void draw(sf::RenderWindow& window);
	void update(float h, float s);
	void update(float h, float s, sf::Vector2f offset);
	void flashHealth();
	void endFlash();
	void setTreasureNumber(int numTreasure);
	void addTreasure();
	bool collectedAllTreasure();

private:
	/*sf::RectangleShape healthBar1;
	sf::RectangleShape healthBar2;
	sf::RectangleShape healthBar3;
	sf::RectangleShape healthBar4;

	sf::RectangleShape staminaBar;*/
	sf::Sound uiSounds[3];
	int collectedTreasure, totalTreasure;
	sf::Text treasure;
	sf::Sprite healthIcon;


	void addSounds();

	bool drawPlease;

	bool showHealth1;
	bool showHealth2;
	bool showHealth3;
	bool showHealth4;
};