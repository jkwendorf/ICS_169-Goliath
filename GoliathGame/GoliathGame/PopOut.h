#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "ButtonManager.h"
#include "TextureManager.h"
#include "Global.h"

class PopOut
{
public:
	PopOut();
	PopOut(std::string& text, std::function<void()> onPressButton1);
	PopOut(std::string& text, std::function<void()> onPressButton1, std::function<void()> onPressButton2);
	~PopOut();
	bool checkActive();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	ButtonManager* bM;
	sf::Sprite background;
	sf::Font* f;
	sf::Text mtext;
	bool isPressedUp, isPressedDown, active;

};