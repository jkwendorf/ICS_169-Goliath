#pragma once
#include <SFML\Graphics.hpp>
#include "Global.h"
#include "TextureManager.h"
//#include "Utility.h"

class Particle
{
public:
	Particle();
	Particle(std::string textureName, sf::Vector2f startingPosition, sf::Vector2f dir, float life, float speed);
	~Particle();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	
	float lifespan, currentLife;
	sf::Sprite particle;
	sf::Vector2f position;
	sf::Vector2f direction;
	float speed;


	//We can add an animation to the particles later if we have time
	//and if we have the artwork for it.

	//Animation particleAnim;
};