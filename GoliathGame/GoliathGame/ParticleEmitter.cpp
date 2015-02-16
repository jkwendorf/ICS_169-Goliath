#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter()
{

}

ParticleEmitter::ParticleEmitter(std::string textureName, sf::Vector2f position, sf::Vector2f dir, float particleLife, float speed, int particleAmount)
	: active(true)
{
	for(int x = 0; x < particleAmount; x++)
	{
		speed += rand() % 250;
		position.x += rand() % 350;
		position.y += rand() % 50;
		particleLife += rand() % 220 / 100;
		particleList.push_back(new Particle(textureName, position, dir, particleLife, speed));
	}
}

ParticleEmitter::~ParticleEmitter()
{
	//Look into why the deletions is causing an exception some other time


	//for(auto iter = particleList.begin(); iter != particleList.end(); iter++)
		//delete *iter;
}

void ParticleEmitter::update(float deltaTime)
{
	if(active)
		for(Particle* a : particleList)
		{
			a->update(deltaTime);
		}
}

void ParticleEmitter::draw(sf::RenderWindow &window)
{
	if(active)
		for(Particle* a : particleList)
			window.draw(a->particle);

	
}