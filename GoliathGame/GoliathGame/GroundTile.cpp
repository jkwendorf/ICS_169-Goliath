
#include "GroundTile.h"

GroundTile::GroundTile()
{
}

GroundTile::GroundTile(int tileNum, sf::Vector2i pos, int tileSheetRows, int tileSheetCols, sf::Texture* texture)
{
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(TILE_HEIGHT * (tileNum % tileSheetCols),
				TILE_WIDTH * (tileNum / tileSheetRows),TILE_WIDTH, TILE_HEIGHT));
	sprite.setPosition(pos.x, pos.y);
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