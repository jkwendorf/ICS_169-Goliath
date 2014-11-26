#pragma once 


class BaseGameScreen
{
public:
	virtual void update(float deltaTime) {};
	virtual void draw(sf::RenderWindow& window) {};
};