#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class State
{
public:
	virtual ~State() {};
	virtual void DeleteState() = 0;
	virtual void update(float deltaTime, sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void handleEvent(sf::Event event) = 0;
	virtual void loadContent() = 0;
	virtual void unloadContent() = 0;
	virtual void setToQuit() = 0;
	
	bool shouldQuit;
};