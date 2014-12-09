#include "InputManager.h"
#include "PhysicsManager.h"

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

	//utility[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	s.running = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !s.isFalling)
	{
		s.jump();
	}
	utility[2] = sf::Mouse::isButtonPressed(sf::Mouse::Right) && !utility[2] ? true : false;
	utility[3] = sf::Mouse::isButtonPressed(sf::Mouse::Left) && !utility[3] ? true : false;
	utility[4] = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !utility[4] ? true : false;
	utility[5] = sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !utility[5] ? true : false;

	playerMove(s, deltaTime);
}

void InputManager::playerMove(Player& player, float deltaTime)
{
	//Change this to player Speed once a player class is made later on.
	//int speed = (utility[0]) ? 4 : 1;
	

	/*
	Player Movement Update
	*/
	

	/*if(movement[0])
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
	}*/

	/* HANDLE LEFT AND RIGHT MOTION*/
	if(movement[0])
	{
		if(!player.hShot.grappleInProgress || !player.hShot.hookedOnSomething)
		{
			player.horizontalAcceleration(LEFT, deltaTime);
			player.facingRight = false;
		}
	}
	else if(movement[1])
	{
		 if(!player.hShot.grappleInProgress || !player.hShot.hookedOnSomething)
		 {
			player.horizontalAcceleration(RIGHT, deltaTime);
			player.facingRight = true;
		 }
	}
	else
		player.horizontalAcceleration(STILL, deltaTime);

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
		{
			utility[3] = false;
			player.currentCooldown = 0.0;
		}
	}
	if(utility[4])
	{
		player.weapon = SWORD;
		std::cout << "Sword switch" << std::endl;
	}
	if(utility[5])
	{
		player.weapon = CROSSBOW;
		std::cout << "Cross Bow Switch" << std::endl;
	}
	//player.sprite.move(player.vel);
	//player.vel.x = 0.0;
}