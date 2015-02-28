#pragma once
#include "Particle.h"

class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(std::string textureName, sf::Vector2f position, sf::Vector2f dir, float particleLife, float speed, int particleAmount, std::string particleEmitterTye);
	~ParticleEmitter();
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	void resetAllParticles();
	std::vector<Particle> particleList;
	//Particle* particles[20];
	void disable();
	void enable();
private:
	//std::vector<Particle*> particleList;
	bool active;
};
