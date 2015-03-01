#include "Particle.h"


Particle::Particle()
{

}

Particle::Particle(std::string textureName, sf::Vector2f startingPosition, sf::Vector2f dir, float life, float speed2) :
	position(startingPosition), direction(dir), lifespan(life), speed(speed2), currentLife(0.0f)
{
	particle.setTexture(*TextureManager::GetInstance().retrieveTexture(textureName));
	particle.setPosition(startingPosition);
	particle.setOrigin(particle.getTextureRect().width / 2.0, particle.getTextureRect().height / 2.0);
	//normalize(direction);
	
}

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
	currentLife += deltaTime;
	if(currentLife >= lifespan)
	{
		currentLife = 0;
		//particle.setPosition(position);
		//particle.setRotation(0.0);
	}
	particle.move(direction.x * speed * deltaTime, direction.y * speed * deltaTime);
	//particle.rotate(2.f);

	
}

void Particle::draw(sf::RenderWindow &window)
{
	//window.draw(particle);
}

void Particle::resetPosition()
{
	position.y += rand() % 400 - 200;
	particle.setPosition(position);
}