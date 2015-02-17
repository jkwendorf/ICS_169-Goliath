
#include "Background.h"


Background::Background(int levelNum, int roomNum)
	:nonMovingLayer(*TextureManager::GetInstance().retrieveTexture(
	Global::GetInstance().roomSizes.at("Level"+ std::to_string(levelNum) + "Room" + std::to_string(roomNum)).nonMovinglayer)),
	vel(-10.0f, 0.0f)
{
	RoomStruct temp = Global::GetInstance().roomSizes.at("Level"+ std::to_string(levelNum) + "Room" + std::to_string(roomNum));
	for (int i = 0; i < temp.movingLayers.size(); i++)
	{
		Layer l;
		l.image = sf::Sprite(*TextureManager::GetInstance().retrieveTexture(temp.movingLayers[i]));
		l.image.setPosition(0.0f, 0.0f);
		l.scale = 1.0f;
		movingLayers.push_back(l);
	}
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
	movingLayers[layerNum].scale = xScale;
}
	
void Background::update(float deltaTime)
{
	for (int i = 0; i < movingLayers.size(); i++)
	{
		float testing = vel.x * movingLayers[i].scale * deltaTime;
		movingLayers[i].image.move(vel * movingLayers[i].scale * deltaTime);
	}
}
	
void Background::draw(sf::RenderWindow& window)
{
	for (int i = movingLayers.size()-1; i >= 0; i--)
	{
		window.draw(movingLayers[i].image);
	}
	window.draw(nonMovingLayer);
}