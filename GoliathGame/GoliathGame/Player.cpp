#include "Player.h"
#include "Global.h"

Player::Player() 
{
	vel = sf::Vector2f(0.0,0.0);
	
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("blah"));
	sprite.setPosition(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
	sprite.setScale(0.2, 0.2);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	weapon = HOOKSHOT;
	weaponCooldown = 2.0f;
	currentCooldown = 0.0f;
	grappleInProgress = false;
	facingRight = true;
}

Player::~Player() 
{

}

void Player::update(float deltaTime)
{
	if(!grappleInProgress)
		if(facingRight)
			hShot.update(sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y - 15));
		else
			hShot.update(sf::Vector2f(sprite.getPosition().x - 60, sprite.getPosition().y - 15));
	else
	{
		hShot.update(deltaTime);
		if(std::abs(hShot.grappleLocation.x - hShot.sprite.getPosition().x) <= 15 && 
			std::abs(hShot.grappleLocation.x - hShot.sprite.getPosition().x) <= 15)
		{
			//Check to see if it hit something, but for now reset the grapple
			grappleInProgress = false;
		}
	}
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
	window.draw(hShot.sprite);

	/* //TESTING CIRCLE
	sf::CircleShape circle = sf::CircleShape(5.0);
	circle.setPosition(sprite.getPosition());
	circle.setFillColor(sf::Color::Red);
	window.draw(circle);
	*/

}

void Player::grapple()
{
	grappleInProgress = true;
	if(facingRight)
		hShot.grappleToLocation(sf::Vector2f(sprite.getPosition().x + 300 , sprite.getPosition().y - 175));
	else
		hShot.grappleToLocation(sf::Vector2f(sprite.getPosition().x - 300 , sprite.getPosition().y - 175));

}