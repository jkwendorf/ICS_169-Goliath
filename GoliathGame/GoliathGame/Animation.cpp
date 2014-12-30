#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(int spriteSheetWidth, int spriteSheetHeight, int pixelWidth, int pixelHeight, float animationSpeed)
	:ssWidth(spriteSheetWidth), ssHeight(spriteSheetHeight), pWidth(pixelWidth), 
	pHeight(pixelHeight), aSpeed(animationSpeed), currAnimTime(0.0f)
{
	source.x = 0.0;
	source.y = 0.0;
}

Animation::~Animation()
{

}

void Animation::update(float deltaTime, sf::Sprite& sprite, int currentAnimation, bool facingRight)
{
	currAnimTime += deltaTime;
	source.y = currentAnimation;
	if(currAnimTime >= aSpeed)
	{
		source.x++;
		if(source.x >= ssWidth/2)
			source.x = 0;
		currAnimTime = 0.0;
	}
	if(facingRight)
		sprite.setTextureRect(sf::IntRect(source.x * pWidth, source.y * pHeight, pWidth, pHeight));
	else
		sprite.setTextureRect(sf::IntRect((source.x + ssWidth/2) * pWidth, source.y * pHeight, pWidth, pHeight));
}
