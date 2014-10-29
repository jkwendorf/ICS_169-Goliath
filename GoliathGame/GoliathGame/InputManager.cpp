#include "InputManager.h"

InputManager::InputManager()
{
	movement[0] = false;
	movement[1] = false;
	for(int x = 0; x < 3; x++)
	{
		utility[x] = false;
		controller[x] = false;
	}
	utility[3] = false;
	controller[1] = true;
}

InputManager::InputManager(int controllerScheme)
{
	//Decide on this once we finialize the controller scheme
	//will change the way input manager handles different aspects
	controller[controllerScheme] = true;
}

InputManager::~InputManager()
{

}

void InputManager::update(Player& s, float deltaTime)
{
	// JW: Players should conserve momentum when jumping.  They shouldn't be able to change directions in midair

	/*
		Player state flag managing
	*/

	//change this when you want more complex movement
	movement[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	movement[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);


	utility[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !utility[1])
	{
		utility[1] = true;
		s.vel.y = -5.0;
	}
	utility[2] = sf::Mouse::isButtonPressed(sf::Mouse::Right) && !utility[2] ? true : false;
	utility[3] = sf::Mouse::isButtonPressed(sf::Mouse::Left) && !utility[3] ? true : false;



	playerMove(s, deltaTime);
}

void InputManager::playerMove(Player& player, float deltaTime)
{
	//Change this to player Speed once a player class is made later on.
	int speed = (utility[0]) ? 4 : 1;
	

	/*
	Player Movement Update
	*/
	

	if(movement[0])
	{
		//r.move(-100*deltaTime, 0.f);
		player.vel.x = -100 * speed * deltaTime;
		player.facingRight = false;
	}
	if(movement[1])
	{
		//r.move(100*deltaTime, 0.f);
		player.vel.x = 100 * speed * deltaTime;
		player.facingRight = true;
	}
	if(utility[1])
	{
	    if(player.vel.y != 0)
			player.vel.y += 5.0 *deltaTime;
		if(player.sprite.getPosition().y > SCREEN_HEIGHT / 2.0)
		{
			player.sprite.setPosition(player.sprite.getPosition().x, SCREEN_HEIGHT / 2.0);
			player.vel.y = 0.0;
			utility[1] = false;
		}
	}
	if(utility[2])
	{
		if(!player.grappleInProgress)
			player.grapple();
		else
			player.currentCooldown += deltaTime;
	}
	if(utility[3])
	{
		player.attack();
		player.currentCooldown += deltaTime;
		if(player.currentCooldown >= player.weaponCooldown)
			utility[3] = false;
	}
	player.sprite.move(player.vel);
	player.vel.x = 0.0;
}