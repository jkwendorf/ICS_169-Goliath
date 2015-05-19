#pragma once
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "Animation.h"

class Projectile : public BaseObject
{
public:
	Projectile();
	Projectile(sf::Vector2f startPos, sf::Vector2f vel, float rotation=0.0f);
	~Projectile();

	sf::Vector2f startLocation;
	sf::Vector2f velocity;
	float startTime, endTime;

	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	void setLocation(sf::Vector2f pos);
	void setVelocity(sf::Vector2f vel);

	bool moving;
	bool drawPlease;
	//for now it has damage
	float damage;
	sf::Texture projectileTexture;
	sf::Vector2i source;
	bool spriteLeftSwitch, spriteRightSwitch;
	int width;
	sf::RectangleShape rectangle;
	Animation bulletAnimation;
};