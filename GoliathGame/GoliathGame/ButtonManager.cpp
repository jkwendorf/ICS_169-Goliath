#include "ButtonManager.h"

ButtonManager::ButtonManager()
	:startingPos(sf::Vector2f(0,0)), offset(15), buttonDim(sf::Vector2f(300, 100)), current(0), canScrollHorizontal(false)
{
	masterTexture = nullptr;
	masterFont = nullptr;
}

ButtonManager::ButtonManager(sf::Vector2f startingPos, int offset, sf::Vector2f buttonDim, sf::Texture* text, sf::Font* font)
	:startingPos(startingPos), offset(offset), buttonDim(buttonDim), current(0), canScrollHorizontal(false)
{
	masterTexture = text;
	masterFont = font;
}

/*ButtonManager::ButtonManager(sf::Vector2f startingPos, int itemsPerCol, int offset, sf::Vector2f buttonDim, sf::Texture* text, sf::Font* font)
	:startingPos(startingPos), itemsPerCol(itemsPerCol), offset(offset), buttonDim(buttonDim), current(0), canScrollHorizontal(true)
{
	masterTexture = text;
	masterFont = font;
}*/

ButtonManager::ButtonManager(sf::Vector2f startingPos, int itemsPerRow, int offset, sf::Vector2f buttonDim, sf::Texture* text, sf::Font* font)
	:startingPos(startingPos), itemsPerRow(itemsPerRow), offset(offset), buttonDim(buttonDim), current(0), canScrollHorizontal(true)
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
	if(!canScrollHorizontal)
		buttonList.push_back(new Button(sf::Vector2f(startingPos.x, startingPos.y + buttonList.size()*(buttonDim.y + offset)), text, buttonDim, masterTexture, masterFont, onPress));
	else
	{
		/*buttonList.push_back(new Button(sf::Vector2f(startingPos.x + (buttonList.size()/itemsPerCol *(buttonDim.x+offset)),
		startingPos.y + (buttonList.size()%itemsPerCol)*(buttonDim.y + offset)),
		text, buttonDim, masterTexture, masterFont, onPress));*/

		buttonList.push_back(new Button(sf::Vector2f(startingPos.x + (buttonList.size()%itemsPerRow *(buttonDim.x+offset)),
		startingPos.y + (buttonList.size()/itemsPerRow)*(buttonDim.y + offset)),
		text, buttonDim, masterTexture, masterFont, onPress));
	}
	if(buttonList.size() == 1)
		buttonList.at(0)->setSelected(true);
}

void ButtonManager::scrollUp()
{
	/*buttonList.at(current)->setSelected(false);
	current--;

	if(current < 0)
		current = buttonList.size() - 1;
	buttonList.at(current)->setSelected(true);*/

	if(canScrollHorizontal && buttonList.size() > itemsPerRow)
	{
		buttonList.at(current)->setSelected(false);
		current -= itemsPerRow;

		if(current < 0)
			current = buttonList.size() + current;
		buttonList.at(current)->setSelected(true);
	}
	else if(!canScrollHorizontal)
	{
		buttonList.at(current)->setSelected(false);
		current--;

		if(current < 0)
			current = buttonList.size() - 1;
		buttonList.at(current)->setSelected(true);
	}
}

void ButtonManager::scrollDown()
{
	/*buttonList.at(current)->setSelected(false);
	current++;
	
	if(current >= buttonList.size())
		current = 0;
	buttonList.at(current)->setSelected(true);*/

	if(canScrollHorizontal && buttonList.size() > itemsPerRow)
	{
		buttonList.at(current)->setSelected(false);
		current += itemsPerRow;
	
		if(current >= buttonList.size())
			current = current - buttonList.size();
		buttonList.at(current)->setSelected(true);
	}
	else if(!canScrollHorizontal)
	{
		buttonList.at(current)->setSelected(false);
		current++;
	
		if(current >= buttonList.size())
			current = 0;
		buttonList.at(current)->setSelected(true);
	}
}

void ButtonManager::scrollLeft()
{
	/*if(canScrollHorizontal && buttonList.size() > itemsPerCol)
	{
		buttonList.at(current)->setSelected(false);
		current -= itemsPerCol;

		if(current < 0)
			current = buttonList.size() + current;
		buttonList.at(current)->setSelected(true);
	}*/

	if(canScrollHorizontal)
	{
		buttonList.at(current)->setSelected(false);
		current--;

		if(current < 0)
			current = buttonList.size() + current;
		buttonList.at(current)->setSelected(true);
	}
}

void ButtonManager::scrollRight()
{
	/*if(canScrollHorizontal && buttonList.size() > itemsPerCol)
	{
		buttonList.at(current)->setSelected(false);
		current += itemsPerCol;

		if(current >= buttonList.size())
			current = current - buttonList.size();
		buttonList.at(current)->setSelected(true);
	}*/
	if(canScrollHorizontal)
	{
		buttonList.at(current)->setSelected(false);
		current++;

		if(current >= buttonList.size())
			current = current - buttonList.size();
		buttonList.at(current)->setSelected(true);
	}
}

void ButtonManager::pressSelectedButton()
{
	int choice = current;
	resetSelectedButton();
	buttonList.at(choice)->pressButton();
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

void ButtonManager::resetSelectedButton()
{
	buttonList.at(current)->setSelected(false);
	current = 0;
	buttonList.at(current)->setSelected(true);
}