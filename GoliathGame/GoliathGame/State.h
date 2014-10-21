#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void handleEvent(sf::Event event) = 0;
	virtual void loadContent() = 0;
	virtual void unloadContent() = 0;
};