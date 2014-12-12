#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
	Button(sf::Vector2f pos, sf::Vector2f buttonDim, sf::Texture* texture, std::function<void()> onPress = [] {});
	Button(sf::Vector2f pos, std::string text, sf::Vector2f buttonDim, sf::Texture* texture, sf::Font* font, std::function<void()> onPress = [] {});
	~Button(void);
	void processClick(sf::Event event);
	void pressButton();
	void draw(sf::RenderWindow& window);

	void setSelected(bool selected);
	void setDimension(sf::Vector2f dim);
	sf::Vector2f getDimension();
	void setFont(sf::Font* font);
	void setTexture(sf::Texture* texture);

private:
	Button(void);
	
	std::function<void ()> onPress;
	sf::Sprite button;
	sf::Text text;
};