#include "ButtonManager.h"

ButtonManager::ButtonManager()
	:startingPos(sf::Vector2f(0,0)), offset(15), buttonDim(sf::Vector2f(300, 100)), current(0)
{
	masterTexture = nullptr;
	masterFont = nullptr;
}

ButtonManager::ButtonManager(sf::Vector2f startingPos, int offset, sf::Vector2f buttonDim, sf::Texture* text, sf::Font* font)
	:startingPos(startingPos), offset(offset), buttonDim(buttonDim), current(0)
{
	masterTexture = text;
	masterFont = font;
}

ButtonManager::~ButtonManager()
{
	for(int i = 0; i < buttonList.size(); i++)
	{
		delete buttonList.at(i);
	}
}

void ButtonManager::createButton(std::string text, std::function<void ()> onPress)
{
	buttonList.push_back(new Button(sf::Vector2f(startingPos.x, startingPos.y + buttonList.size()*(buttonDim.y + offset)), text, buttonDim, masterTexture, masterFont, onPress));
	if(buttonList.size() == 1)
		buttonList.at(0)->setSelected(true);
}

void ButtonManager::scrollUp()
{
	buttonList.at(current)->setSelected(false);
	current--;

	if(current < 0)
		current = buttonList.size() - 1;
	buttonList.at(current)->setSelected(true);
}

void ButtonManager::scrollDown()
{
	buttonList.at(current)->setSelected(false);
	current++;
	
	if(current >= buttonList.size())
		current = 0;
	buttonList.at(current)->setSelected(true);
}

void ButtonManager::pressSelectedButton()
{
	buttonList.at(current)->pressButton();
}

void ButtonManager::draw(sf::RenderWindow& window)
{
	for(int i = 0; i < buttonList.size(); i++)
		buttonList.at(i)->draw(window);
}

void ButtonManager::setStartingPos(sf::Vector2f pos)
{
	startingPos = pos;
}

sf::Vector2f ButtonManager::getStartingPos()
{
	return startingPos;
}

void ButtonManager::setOffset(int newOffset)
{
	offset = newOffset;
}

int ButtonManager::getOffset()
{
	return offset;
}

void ButtonManager::setMasterTexture(sf::Texture* newText)
{
	masterTexture = newText;

	for(int i = 0; i < buttonList.size(); i++)
		buttonList.at(i)->setTexture(newText);
}

sf::Texture* ButtonManager::getMasterTexture()
{
	return masterTexture;
}

void ButtonManager::setMasterFont(sf::Font* newFont)
{
	masterFont = newFont;

	for(int i = 0; i < buttonList.size(); i++)
		buttonList.at(i)->setFont(newFont);
}

sf::Font* ButtonManager::getMasterFont()
{
	return masterFont;
}

void ButtonManager::setButtonDimension(sf::Vector2f dim)
{
	buttonDim = dim;

	for(int i = 0; i < buttonList.size(); i++)
		buttonList.at(i)->setDimension(dim);
}

sf::Vector2f ButtonManager::getButtonDimension()
{
	return buttonDim;
}