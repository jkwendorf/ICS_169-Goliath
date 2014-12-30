#pragma once
#include <SFML\Graphics.hpp>
#include "TextureManager.h"

class Animation
{
public:
	Animation();
	Animation(int spriteSheetWidth, int spriteSheetHeight, int pixelWidth, int pixelHeight, float animationSpeed);
	~Animation();
	void update(float deltaTime,sf::Sprite& sprite, int currentAnimation, bool facingRight);

private:
	sf::Texture* ssTexture;
	sf::Sprite* pSprite;
	sf::Vector2i source;
	int ssWidth, ssHeight, pWidth, pHeight;
	float aSpeed, currAnimTime;
};