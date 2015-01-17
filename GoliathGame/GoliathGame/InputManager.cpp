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

	currentInputCooldown = 1.0;
	inputCooldown = 1.0;

	currentWeaponSwitchCooldown = 1.0;
	weaponSwitchCooldown = 1.0;

	currentGrappleCooldown = .5;
	grappleCooldown = .5;
	
	viewChanged = 0;
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

void InputManager::update(Player& s, sf::View* v, float deltaTime)
{
	// JW: Players should conserve momentum when jumping.  They shouldn't be able to change directions in midair

	/*
		Player state flag managing
	*/

	//change this when you want more complex movement
	movement[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -25);
	movement[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 25);

	//utility[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	
	s.running = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::getAxisPosition(0, sf::Joystick::Z) > 25;
	utility[1] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0)) && !utility[1] ? true : false;
	/*
	{
		if(!s.isHanging && !s.isFalling)
			s.jump();
		else if(s.isHanging && !s.isVaulting)
		{
			s.interpolateVaultAboveGrappleTile();
			//s.instantVaultAboveGrappleTile();
		}
	}
	*/
	utility[2] = (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Joystick::isButtonPressed(0, 1)) && !utility[2] ? true : false;
	utility[3] = (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 2)) && !utility[3] ? true : false;
	utility[4] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::isButtonPressed(0, 3)) && !utility[4] ? true : false;
	utility[5] = (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -25) && !utility[6] ? true : false;
	utility[6] = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 25) && !utility[5] ? true : false;

	playerMove(s, deltaTime);
	viewMove(v, s, deltaTime);

	currentInputCooldown += deltaTime;
	currentWeaponSwitchCooldown += deltaTime;
	currentGrappleCooldown += deltaTime;
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
		if((!player.hShot.grappleInProgress || !player.hShot.hookedOnSomething) && !player.isHanging)
		{
			if(player.running)
				player.stamina--;
			player.horizontalAcceleration(LEFT, deltaTime);
			player.facingRight = false;
		}
	}
	else if(movement[1])
	{
		 if((!player.hShot.grappleInProgress || !player.hShot.hookedOnSomething) && !player.isHanging)
		 {
			if(player.running)
				player.stamina--;
			player.horizontalAcceleration(RIGHT, deltaTime);
			player.facingRight = true;
		 }
	}
	else
		player.horizontalAcceleration(STILL, deltaTime);

	if(utility[1])
	{
		if(!player.isHanging && !player.isFalling)
			player.jump();
		else if(player.isHanging && !player.isVaulting)
		{
			player.interpolateVaultAboveGrappleTile();
			//s.instantVaultAboveGrappleTile();
		}
	}
	if(utility[2])
	{
		if(currentGrappleCooldown >= grappleCooldown)
		{
			if(!player.hShot.isDisabled)
			{
				if(!player.isHanging)
				{
					if(!player.grappleInProgress && !player.isHanging && !player.isVaulting)
					{
						player.grapple();
						currentGrappleCooldown = 0;
					}
					else
						player.currentCooldown += deltaTime;
				}
				else if(!player.isVaulting)
				{
					player.isHanging = false;
					player.hShot.isDisabled = true;
				}
			}
		}
	}
	if(utility[3])
	{
		if(currentInputCooldown >= inputCooldown)
		{
			player.attack();
			player.currentCooldown += deltaTime;
			if(player.currentCooldown >= player.weaponCooldown)
			{
				utility[3] = false;
				player.currentCooldown = 0.0;
			}
			currentInputCooldown = 0.0;
		}
	}
	if(utility[4])
	{
		if(currentWeaponSwitchCooldown >= weaponSwitchCooldown)
		{
			if(player.weapon == CROSSBOW)
			{
				player.weapon = SWORD;
				inputCooldown = 1.25;
				std::cout << "Sword switch" << std::endl;
			}
			else if(player.weapon == SWORD)
			{
				player.weapon = CROSSBOW;
				inputCooldown = .25;
				std::cout << "Cross Bow Switch" << std::endl;
			}
			currentWeaponSwitchCooldown = 0.0;
		}
	}

	//player.sprite.move(player.vel);
	//player.vel.x = 0.0;
}

void InputManager::viewMove(sf::View* v, Player& s, float deltaTime)
{
	viewDifference = 100.0f*deltaTime;	
	if(s.vel.x == 0 && s.vel.y == 0 && !s.grappleInProgress)
	{
		if(utility[5])
		{
			viewChanged -= viewDifference;
			if(viewChanged < Global::GetInstance().yOffset * (-4) && viewChanged < 0)
			{
				viewDifference = 0;
				viewChanged = Global::GetInstance().yOffset * -4;
			}
			Global::GetInstance().topLeft.y -= viewDifference;
			if(s.atBottomEdge)
			{
				v->reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y + viewChanged, SCREEN_WIDTH, SCREEN_HEIGHT));
				s.ui->updateDifferent(s.health, s.stamina, Global::GetInstance().topLeft.y + viewChanged);
			}
		}
		else if(utility[6])
		{
			viewChanged += viewDifference;
			if(viewChanged > Global::GetInstance().yOffset * 4 && viewChanged > 0)
			{
				viewDifference = 0;
				viewChanged = Global::GetInstance().yOffset * 4;
			}
			Global::GetInstance().topLeft.y += viewDifference;
			if(s.atTopEdge || !s.atTheBottom)
			{
				v->reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y + viewChanged, SCREEN_WIDTH, SCREEN_HEIGHT));
				s.ui->updateDifferent(s.health, s.stamina, Global::GetInstance().topLeft.y + viewChanged);
			}
		}		
		else
		{
			Global::GetInstance().topLeft.y -= viewChanged;
			viewChanged = 0;
		}

		//std::cout << viewChanged << std::endl;
		//std::cout << Global::GetInstance().yOffset << std::endl;
	}
	else
	{
		Global::GetInstance().topLeft.y -= viewChanged;
		viewChanged = 0;
	}
}