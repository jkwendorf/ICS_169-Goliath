#include "Button.h"

Button::Button()
{
	onPress = [] {};
}

Button::Button(sf::Vector2f pos, sf::Vector2f buttonDim, sf::Texture* texture, std::function<void()> onPress)
{
	this->onPress = onPress;
	button.setTexture(*texture);
	button.setScale(buttonDim.x/button.getGlobalBounds().width, buttonDim.y/button.getGlobalBounds().height);
	button.setPosition(pos);
	text.setString("");
}

Button::Button(sf::Vector2f pos, std::string text, sf::Vector2f buttonDim, sf::Texture* texture, sf::Font* font, std::function<void()> onPress)
{
	this->onPress = onPress;
	button.setTexture(*texture);
	button.setScale(buttonDim.x/button.getGlobalBounds().width, buttonDim.y/button.getGlobalBounds().height);
	button.setPosition(pos);
	this->text.setString(text);
	this->text.setFont(*font);
	this->text.setColor(sf::Color::Black);
	this->text.setCharacterSize(36);
	this->text.setPosition((int)((button.getPosition().x + buttonDim.x/2) - this->text.getLocalBounds().width/2), (int)((button.getPosition().y + buttonDim.y/2) - (this->text.getLocalBounds().height + 20)/2));
}

Button::~Button(void)
{
}

void Button::processClick(sf::Event event)
{
	if(button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && event.type == sf::Event::MouseButtonPressed)
		onPress();
}

void Button::pressButton()
{
	onPress();
}

void Button::draw(sf::RenderWindow& window)
{
	if(button.getTexture() != NULL)
		window.draw(button);
	if(text.getFont())
	{
		window.draw(text);
	}
}

void Button::setDimension(sf::Vector2f dim)
{
	button.setScale(dim.x/button.getGlobalBounds().width, dim.y/button.getGlobalBounds().height);
	text.setScale(dim.x/this->text.getGlobalBounds().width, dim.y/this->text.getGlobalBounds().height);
}

sf::Vector2f Button::getDimension()
{
	return sf::Vector2f(button.getGlobalBounds().width, button.getGlobalBounds().height);
}

void Button::setFont(sf::Font* font)
{
	text.setFont(*font);
}

void Button::setTexture(sf::Texture* texture)
{
	button.setTexture(*texture);
}

void Button::setSelected(bool selected)
{
	if(selected)
		text.setColor(sf::Color::Yellow);
	else
		text.setColor(sf::Color::Black);
}