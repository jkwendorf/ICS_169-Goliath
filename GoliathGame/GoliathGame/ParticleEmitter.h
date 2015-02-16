#pragma once
#include "Particle.h"

class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(std::string textureName, sf::Vector2f position, sf::Vector2f dir, float particleLife, float speed, int particleAmount);
	~ParticleEmitter();
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	std::vector<Particle*> particleList;
	void disable();
	void enable();
private:
	//std::vector<Particle*> particleList;
	bool active;
};
