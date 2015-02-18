
#include "Background.h"


Background::Background(int levelNum, int roomNum)
	:nonMovingLayer(*TextureManager::GetInstance().retrieveTexture(
	Global::GetInstance().roomSizes.at("Level"+ std::to_string(levelNum) + "Room" + std::to_string(roomNum)).nonMovinglayer)),
	vel(-100.0f, -100.0f)
{
	RoomStruct temp = Global::GetInstance().roomSizes.at("Level"+ std::to_string(levelNum) + "Room" + std::to_string(roomNum));
	for (int i = 0; i < temp.movingLayers.size(); i++)
	{
		Layer l;
		l.image = sf::Sprite(*TextureManager::GetInstance().retrieveTexture(temp.movingLayers[i].imageName));
		l.image.setPosition(0.0f, 0.0f);
		l.image.scale(2.0f, 2.0f);
		l.scale = temp.movingLayers[i].scale;
		movingLayers.push_back(l);
	}
	nonMovingLayer.setPosition(320.0f, 0.0f);
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
	
void Background::update(float deltaTime)
{
	for (int i = 0; i < movingLayers.size(); i++)
	{
		movingLayers[i].image.move(sf::Vector2f(vel.x * movingLayers[i].scale.x * deltaTime, vel.y * movingLayers[i].scale.y * deltaTime));
		if (movingLayers[i].image.getPosition().y + movingLayers[i].image.getGlobalBounds().height 
			< nonMovingLayer.getPosition().y + nonMovingLayer.getGlobalBounds().height)
		{
			//reset();
			vel.y *= -1;
		
		}
		else if (movingLayers[i].image.getPosition().y > nonMovingLayer.getPosition().y) {
			vel.y *= -1;
		}
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

void Background::reset()
{
	for (int i = 0; i < movingLayers.size(); i++)
	{
		movingLayers[i].image.setPosition(0,0);
	}
}