#include "NonMovingLayer.h"


NonMovingLayer::NonMovingLayer(RoomStruct& roomstrct, int layerNum)
{
	image = sf::Sprite(*TextureManager::GetInstance().retrieveTexture(roomstrct.movingLayers[layerNum].imageName));
	image.setPosition(roomstrct.movingLayers.at(layerNum).posOffset.x, roomstrct.movingLayers.at(layerNum).posOffset.y);
	image.setScale(roomstrct.movingLayers.at(layerNum).sizeScale.x, roomstrct.movingLayers.at(layerNum).sizeScale.y);
	inFront = roomstrct.movingLayers.at(layerNum).drawInFront;
}

void NonMovingLayer::Update()
{
}

void NonMovingLayer::draw(sf::RenderWindow& window)
{
	window.draw(image);
}
