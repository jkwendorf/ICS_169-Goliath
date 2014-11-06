
#include "GroundTile.h"

GroundTile::GroundTile()
{
}

GroundTile::GroundTile(int tileNum, const sf::Vector2i& pos, const sf::Vector2i& screenOffSet, const sf::Vector2f& scale, sf::Texture* texture)
	:BaseObject(true), offSet(screenOffSet)
{
	sprite.setTexture(*texture);
	sf::IntRect temp = sf::IntRect(EDITOR_TILE_HEIGHT * (tileNum % TileSheetRows),
				EDITOR_TILE_WIDTH * (tileNum / TileSheetRows),EDITOR_TILE_WIDTH, EDITOR_TILE_HEIGHT);
	//std::cout << "Pos x: " <<  temp.left << ". Pos Y: " << temp.top << std::endl;
	sprite.setTextureRect(temp);
	//std::cout << "Pos x: " <<  pos.x << ". Pos Y: " << pos.y << std::endl;
	sprite.setPosition(pos.x + offSet.x /*- cameraOffSet.x*/, pos.y + offSet.y /*- cameraOffSet.y*/);
	sprite.setScale((float)scale.x, (float)scale.y / EDITOR_TILE_HEIGHT);
	//std::cout << "Scale x: " <<  sprite.getScale().x << ". Scale Y: " << sprite.getScale().y << std::endl;
}

GroundTile::~GroundTile()
{

}

void GroundTile::draw(sf::RenderWindow& window)
{
	BaseObject::draw(window);
}