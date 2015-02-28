#include "Layer.h"

Layer::Layer(RoomStruct& roomStrct, int layerNum)
{
	image[0] = sf::Sprite(*TextureManager::GetInstance().retrieveTexture(roomStrct.movingLayers[layerNum].imageName));
	//l.image.setPosition(0.0f, 0.0f);
	std::cout << "Herp derp: " << roomStrct.movingLayers[layerNum].posOffset.x << " " << roomStrct.movingLayers[layerNum].posOffset.y << std::endl;
	image[0].setPosition(roomStrct.movingLayers[layerNum].posOffset.x, roomStrct.movingLayers[layerNum].posOffset.y);
	//image[0].setPosition(roomStrct.
	//image[0].setOrigin(image[0].getGlobalBounds().left/2, image[0].getGlobalBounds().top/2);
	image[0].scale(2.0f, 2.0f);
	image[1] = sf::Sprite(*TextureManager::GetInstance().retrieveTexture(roomStrct.movingLayers[layerNum].imageName));
	//l.image.setPosition(0.0f, 0.0f);
	std::cout << image[0].getGlobalBounds().left << std::endl;
	image[1].setPosition(image[0].getGlobalBounds().left + image[0].getGlobalBounds().width, 
		image[0].getGlobalBounds().top);
	//image[1].setOrigin(image[0].getGlobalBounds().left/2, image[0].getGlobalBounds().top/2);
	image[1].scale(2.0f, 2.0f);
	scale = roomStrct.movingLayers[layerNum].scale;
	degrees = roomStrct.movingLayers[layerNum].degrees;
	timeToRotate = roomStrct.movingLayers[layerNum].timeToRotate;
	posOffset = roomStrct.movingLayers[layerNum].posOffset;
	currentDegrees = 0;
	rotateForward = false;
}
	
void Layer::update(float deltaTime, sf::Vector2f& vel)
{
	for(int i = 0; i < 2; i++)
	{
		if (!rotateForward)
			image[i].move(sf::Vector2f(vel.x * scale.x * deltaTime, vel.y * scale.y * deltaTime));
		//std::cout << "Pos: " << image[i].getGlobalBounds().left << ", " << image[i].getGlobalBounds().left + image[i].getGlobalBounds().width <<
		//	", " << vel.y << std::endl;
		if(image[i].getGlobalBounds().left + image[i].getGlobalBounds().width < mViewX)
		{
			std::cout << "things should be getting reset" << std::endl;
			int j = (i == 0 ? 1 : 0);
			image[i].setPosition(image[j].getGlobalBounds().left + image[j].getGlobalBounds().width, image[j].getGlobalBounds().top);
		}
		//std::cout << "Pos" << i << ": " << image[i].getGlobalBounds().left << ", " << image[i].getGlobalBounds().top << std::endl;
		//if (movingLayers[i].rotateForward) {
		//	movingLayers[i].currentDegrees += deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate;
		//	movingLayers[i].image.rotate(deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate);
		//	if (movingLayers[i].currentDegrees > movingLayers[i].degrees)
		//		movingLayers[i].rotateForward = false;
		//}
		//else {
		//	movingLayers[i].currentDegrees -= deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate;
		//	movingLayers[i].image.rotate(-deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate);
		//	if (movingLayers[i].currentDegrees < 0)
		//		movingLayers[i].rotateForward = true;
		//}	
	}
}
	
void Layer::draw(sf::RenderWindow& window)
{
	for(int i = 0; i < 2; i++)
	{
		if(image[i].getGlobalBounds().left < mViewX + SCREEN_WIDTH)
		{
			window.draw(image[i]);
		}
	}

}

void Layer::reset()
{
	image[0].setPosition(0,0);
	image[1].setPosition(image[0].getGlobalBounds().left + image[0].getGlobalBounds().width,posOffset.y);
}

void Layer::setViewX(float viewX)
{
	mViewX = viewX;
}