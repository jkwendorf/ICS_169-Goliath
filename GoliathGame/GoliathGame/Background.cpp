
#include "Background.h"


Background::Background(int levelNum, int roomNum)
	:nonMovingLayer(*TextureManager::GetInstance().retrieveTexture(
	Global::GetInstance().roomSizes.at("Level"+ std::to_string(levelNum) + "Room" + std::to_string(roomNum)).nonMovinglayer)),
	vel(-300.0f, -100.0f)
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
	for (int i = 0; i < movingLayers.size(); i++)
	{
		movingLayers[i].setViewX(viewX);
		movingLayers[i].update(deltaTime, vel);
		//if (movingLayers[i].image[i].getPosition().y + movingLayers[i].image[i].getGlobalBounds().height 
		//	< nonMovingLayer.getPosition().y + nonMovingLayer.getGlobalBounds().height)
		//{
		//	//reset();
		//	vel.y *= -1;
		//	//movingLayers[i].currentDegrees += deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate;
		//	//movingLayers[i].image.rotate(deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate);
		//	//if (movingLayers[i].currentDegrees > movingLayers[i].degrees) {
		//	//	movingLayers[i].rotateForward = false;
		//	//	vel.y *= -1;
		//	//}
		//
		//}
		//else if (movingLayers[i].image[i].getPosition().y > nonMovingLayer.getPosition().y) 
		//{
		//	vel.y *= -1;
		//	
		//	//movingLayers[i].currentDegrees -= deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate;
		//	//movingLayers[i].image.rotate(deltaTime * movingLayers[i].degrees/movingLayers[i].timeToRotate);
		//	//if (movingLayers[i].currentDegrees > movingLayers[i].degrees) {
		//	//	movingLayers[i].rotateForward = false;
		//	//	vel.y *= -1;
		//	//}
		//}
	}
}
	
void Background::draw(sf::RenderWindow& window)
{
	for (int i = movingLayers.size()-1; i >= 0; i--)
	{
		movingLayers[i].draw(window);
	}
	window.draw(nonMovingLayer);
}

void Background::reset()
{
	for (int i = 0; i < movingLayers.size(); i++)
	{
		movingLayers[i].reset();
	}
}