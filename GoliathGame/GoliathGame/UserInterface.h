#pragma once

#include <SFML/Graphics.hpp>

class UserInterface
{
public:
	UserInterface(float h, float s);
	~UserInterface();

	void draw(sf::RenderWindow& window);
	void update(float h, float s);

private:
	sf::RectangleShape healthBar;
	sf::RectangleShape staminaBar;
};