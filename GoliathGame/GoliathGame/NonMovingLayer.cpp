#include "NonMovingLayer.h"


NonMovingLayer::NonMovingLayer(RoomStruct& roomstrct, int layerNum)
	:degreesToRotate(3), timeToRotate(3)
{
	image = sf::Sprite(*TextureManager::GetInstance().retrieveTexture(roomstrct.movingLayers[layerNum].imageName));
	image.setPosition(roomstrct.movingLayers.at(layerNum).posOffset.x, roomstrct.movingLayers.at(layerNum).posOffset.y);
	image.setScale(roomstrct.movingLayers.at(layerNum).sizeScale.x, roomstrct.movingLayers.at(layerNum).sizeScale.y);
	image.setOrigin(0,50);
	scale.x = roomstrct.movingLayers.at(layerNum).scale.x;
	scale.y = roomstrct.movingLayers.at(layerNum).scale.y;
	inFront = roomstrct.movingLayers.at(layerNum).drawInFront;
}

void NonMovingLayer::Update(float deltaTime, sf::Vector2f vel)
{
	//image.move(sf::Vector2f(vel.x * scale.x * deltaTime, vel.y * scale.y * deltaTime));
	//currentDegrees += deltaTime * degreesToRotate/timeToRotate;
	//currentTime += deltaTime;
	//if (timeToRotate > currentTime) {
	//	//image.rotate(currentDegrees);
	//	image.setRotation(currentDegrees);
	//}
}

void NonMovingLayer::draw(sf::RenderWindow& window)
{
	window.draw(image);
}
