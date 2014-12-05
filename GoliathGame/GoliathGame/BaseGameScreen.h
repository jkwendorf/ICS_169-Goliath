#pragma once 

#include <SFML/Graphics.hpp>

class BaseGameScreen
{
public:
	virtual void update(float deltaTime) {};
	virtual void draw(sf::RenderWindow& window) {};
	virtual void DeleteLevel() {};
	virtual void CheckChangeScreen(BaseGameScreen*& newScreen) {};
};