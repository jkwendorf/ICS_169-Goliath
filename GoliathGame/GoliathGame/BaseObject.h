#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Global.h"

class BaseObject
{
public:
	// METHODS AND FUNCTIONS
	BaseObject();
	BaseObject(bool canCollide);
	BaseObject(int testing, int objectNum, const sf::Vector2i& pos, const sf::Vector2i& sectionOffSet, float scale, sf::Texture* texture, bool canCollide = true);
	~BaseObject();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void print();
	
	// VARIABLES
	sf::Sprite sprite;
	sf::Vector2f vel;
	bool isFalling;
	bool collidable;
	int objectNum, testingNum;
};