
#include "GroundTile.h"

GroundTile::GroundTile()
{
}

GroundTile::GroundTile(int tileNum, sf::Vector2i pos, sf::Vector2i scale, sf::Texture* texture)
	:offSetX(0), offSetY(0)
{
	sprite.setTexture(*texture);
	sf::IntRect temp = sf::IntRect(TILE_HEIGHT * (tileNum % TileSheetRows),
				TILE_WIDTH * (tileNum / TileSheetRows),TILE_WIDTH, TILE_HEIGHT);
	//std::cout << "Pos x: " <<  temp.left << ". Pos Y: " << temp.top << std::endl;
	sprite.setTextureRect(temp);
	//std::cout << "Pos x: " <<  pos.x << ". Pos Y: " << pos.y << std::endl;
	sprite.setPosition(pos.x + offSetX, pos.y + offSetY);
	sprite.setScale((float)scale.x / TILE_WIDTH, (float)scale.y / TILE_HEIGHT);
	//std::cout << "Scale x: " <<  sprite.getScale().x << ". Scale Y: " << sprite.getScale().y << std::endl;
}

GroundTile::~GroundTile()
{

}

sf::Sprite GroundTile::getSprite()
{
	return sprite;
}

void GroundTile::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}