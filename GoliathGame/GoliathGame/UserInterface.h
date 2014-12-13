#pragma once

#include <SFML/Graphics.hpp>

class UserInterface
{
public:
	UserInterface(float h, float s);
	~UserInterface();

	void draw(sf::RenderWindow& window);
	void update(float h, float s);
	void updateDifferent(float h, float s, float offset);

private:
	sf::RectangleShape healthBar;
	sf::RectangleShape staminaBar;
};