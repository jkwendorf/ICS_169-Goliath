#pragma once
#include <vector>
#include "Button.h"

class ButtonManager
{
public:
	ButtonManager(sf::Vector2f startingPos, int offset, sf::Vector2f buttonDim, sf::Texture* text, sf::Font* font);
	~ButtonManager();

	void createButton(std::string text, std::function<void ()> onPress);
	void scrollUp();
	void scrollDown();
	void pressSelectedButton();

	void draw(sf::RenderWindow& window);

	void setStartingPos(sf::Vector2f pos);
	sf::Vector2f getStartingPos();
	void setOffset(int newOffset);
	int getOffset();
	void setMasterTexture(sf::Texture* newText);
	sf::Texture* getMasterTexture();
	void setMasterFont(sf::Font* newFont);
	sf::Font* getMasterFont();
	void setButtonDimension(sf::Vector2f dim);
	sf::Vector2f getButtonDimension();

private:
	ButtonManager();
	std::vector<Button*> buttonList;
	int offset, current;
	sf::Vector2f startingPos, buttonDim;
	sf::Texture* masterTexture;
	sf::Font* masterFont;
};

