#include "Button.h"

Button::Button()
{
	onPress = [] {};
}

Button::Button(sf::Vector2f pos, sf::Texture* image, std::function<void()> onPress)
{
	this->onPress = onPress;
	button.setTexture(*image);
	button.setPosition(pos);
}

Button::~Button(void)
{
}

void Button::processClick(sf::Event event)
{
	if(button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		onPress();
}

void Button::draw(sf::RenderWindow& window)
{
	if(button.getTexture() != NULL)
		window.draw(button);
}