#include "Player.h"
#include "Global.h"

Player::Player() 
{
	vel = sf::Vector2f(0.0,0.0);
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));
	sprite.setPosition(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
	sprite.setScale(0.2, 0.2);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	weapon = HOOKSHOT;
}

Player::~Player() 
{

}

void Player::update(float deltaTime)
{

}

void Player::attack()
{

}

void Player::move(float x, float y)
{
	sprite.move(x, y);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}