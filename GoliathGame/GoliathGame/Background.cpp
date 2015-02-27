
#include "Background.h"


Background::Background(int levelNum, int roomNum)
	:nonMovingLayer(*TextureManager::GetInstance().retrieveTexture(
	Global::GetInstance().roomSizes.at("Level"+ std::to_string(levelNum) + "Room" + std::to_string(roomNum)).nonMovinglayer)),
	vel(-300.0f, 99.0f), hitGround(false), timerForStep(-1.0f)
{
	RoomStruct temp = Global::GetInstance().roomSizes.at("Level"+ std::to_string(levelNum) + "Room" + std::to_string(roomNum));
	for (int i = 0; i < temp.movingLayers.size(); i++)
	{
		movingLayers.push_back(Layer(temp, i));
	}
	nonMovingLayer.setPosition(temp.posOffset.x, temp.posOffset.y);
}


Background::~Background()
{

}

void Background::setScale(int layerNum, float xScale, float yScale)
{
	if(layerNum >= movingLayers.size())
	{
		std::cout << "This is not in the list" << std::endl;
		return;
	}
	movingLayers[layerNum].scale.x = xScale;
	movingLayers[layerNum].scale.y = yScale;
}
	
void Background::update(float deltaTime, float viewX)
{

	if(!movingLayers.empty())
	{
		if(timerForStep == -1.0f)
		{
			//Move up
			if (movingLayers[2].image[1].getPosition().y > nonMovingLayer.getGlobalBounds().height)
			{
				std::cout << "Move Up" << std::endl;
				//reset();
				vel.y = -100;

				//movingLayers[i].currentDegrees += deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate;
				//movingLayers[i].image.rotate(deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate);
				//if (movingLayers[i].currentDegrees > movingLayers[i].degrees) {
				//	movingLayers[i].rotateForward = false;
				//	vel.y *= -1;
				//}
	
			}
			// Move down
			else if (movingLayers[2].image[1].getPosition().y + movingLayers[2].image[1].getGlobalBounds().height <
				nonMovingLayer.getPosition().y + nonMovingLayer.getGlobalBounds().height && vel.y != 99) 
			{
				std::cout << "Move Down" << std::endl;
				//vel.y = 100;
				vel.x = 0;
				vel.y = 0;

				//Switch boolean over hurrrr
				hitGround = true;
				timerForStep = 0.0f;
				//movingLayers[i].currentDegrees -= deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate;
				//movingLayers[i].image.rotate(deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate);
				//if (movingLayers[i].currentDegrees > movingLayers[i].degrees) {
				//	movingLayers[i].rotateForward = false;
				//	vel.y *= -1;
				//}
			}
		}
		else if(timerForStep != -1.0f && timerForStep < 2.0f)
		{
			timerForStep += deltaTime;

			if(timerForStep >= 2.0f)
			{
				timerForStep = -1.0f;
				vel.x = -300.f;
				vel.y = 100.f;
			}
		}
	}
	for (int i = 0; i < movingLayers.size(); i++)
	{
		movingLayers[i].setViewX(viewX);
		movingLayers[i].update(deltaTime, vel);

		std::cout << "Layer: " << i << " Pos: " << movingLayers[i].image[i].getPosition().y << std::endl;

		// Move up
		/*if (movingLayers[i].image[i].getPosition().y + movingLayers[i].image[i].getGlobalBounds().height 
			< nonMovingLayer.getPosition().y + nonMovingLayer.getGlobalBounds().height)*/
	}

	std::cout << "Hi Tyler" << std::endl;
}
	
void Background::draw(sf::RenderWindow& window)
{
	for (int i = movingLayers.size()-1; i >= 0; i--)
	{
		movingLayers[i].draw(window);
	}
	window.draw(nonMovingLayer);
}

void Background::setHitFloor(bool b) {
	hitGround = b;
}

bool Background::hitFloor() {
	return hitGround;
}

void Background::reset()
{
	for (int i = 0; i < movingLayers.size(); i++)
	{
		movingLayers[i].reset();
	}
}