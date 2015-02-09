#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Defines.h"
#include <iostream>

class BaseObject
{
public:
	// METHODS AND FUNCTIONS
	BaseObject();
	BaseObject(bool canCollide);
	BaseObject(int objectNum_);
	BaseObject(int testing, int objectNum, const sf::Vector2i& pos, const sf::Vector2i& sectionOffSet, float scale, sf::Texture* texture, bool canCollide = true, bool grappleable = false, bool interactable = false);
	~BaseObject();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void print();
	
	// VARIABLES
	sf::Sprite sprite;
	sf::Vector2f vel;
	bool isFalling;
	bool collidable;
	bool grappleable;
	bool interactable;
	int objectNum, testingNum, jumpSpeed, moveSpeed, moveAccel, boostSpeed, grappleSpeed, gravity, fallSpeed;
};