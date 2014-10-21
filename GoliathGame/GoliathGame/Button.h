#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
	Button(sf::Vector2f pos, sf::Texture* image, std::function<void()> onPress = [] {});
	~Button(void);
	void processClick(sf::Event event);
	void draw(sf::RenderWindow& window);

	std::function<void ()> onPress;

private:
	Button(void);
	sf::Sprite button;
};