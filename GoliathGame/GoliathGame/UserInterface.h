#pragma once

#include <SFML/Graphics.hpp>

class UserInterface
{
public:
	UserInterface(float h, float s);
	~UserInterface();

	void resetUI();
	void draw(sf::RenderWindow& window);
	void update(float h, float s);
	void updateDifferent(float h, float s, sf::Vector2f offset);

private:
	/*sf::RectangleShape healthBar1;
	sf::RectangleShape healthBar2;
	sf::RectangleShape healthBar3;
	sf::RectangleShape healthBar4;

	sf::RectangleShape staminaBar;*/

	sf::Sprite healthIcon;

	bool showHealth1;
	bool showHealth2;
	bool showHealth3;
	bool showHealth4;
};