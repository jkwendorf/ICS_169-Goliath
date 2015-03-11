#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(int spriteSheetWidth, int spriteSheetHeight, int pixelWidth, int pixelHeight, float animationSpeed, bool once = false)
	:ssWidth(spriteSheetWidth), ssHeight(spriteSheetHeight), pWidth(pixelWidth), playOnce(once), 
	pHeight(pixelHeight), aSpeed(animationSpeed), currAnimTime(0.0f), isDone(false)
{
	source.x = 0.0;
	source.y = 0.0;
}

Animation::~Animation()
{

}

void Animation::update(float deltaTime, sf::Sprite& sprite, int currentAnimation, bool facingRight)
{
	if (isDone)
		return;
	currAnimTime += deltaTime;
	source.y = currentAnimation;
	if(currAnimTime >= aSpeed)
	{
		source.x++;
		if(source.x >= ssWidth/2) {
			source.x = 0;
			if (playOnce)
				isDone = true;
		}
		currAnimTime = 0.0;
	}
	if(facingRight)
		sprite.setTextureRect(sf::IntRect(source.x * pWidth, source.y * pHeight, pWidth, pHeight));
	else
		//if (!playOnce)
		//	sprite.setTextureRect(sf::IntRect((source.x + ssWidth/2) * pWidth, source.y * pHeight, pWidth, pHeight));
		//else
			sprite.setTextureRect(sf::IntRect((ssWidth - source.x - 1) * pWidth, source.y * pHeight, pWidth, pHeight));
}

bool Animation::isAnimationDone()
{
	return isDone;
}

void Animation::reset() 
{
	isDone = false;
}
