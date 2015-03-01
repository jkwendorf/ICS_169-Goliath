#include "InputManager.h"
#include "PhysicsManager.h"
#include "JumpingState.h"

InputManager::InputManager()
	:grappleReset(true)
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
	
	viewChangedX = 0;
	viewChangedY = 0;

	//sch.moveCommand = new MoveCommand();
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

void InputManager::update(Player& s, Camera* camera, float deltaTime)
{
	// JW: Players should conserve momentum when jumping.  They shouldn't be able to change directions in midair

	/*
		Player state flag managing
	*/

	//change this when you want more complex movement
	//movement[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -25);
	//movement[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 25);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -25))
	{
		MoveCommand* move = new MoveCommand();
		move->init(&s, LEFT, deltaTime, MOVELEFT);
		s.inputQueue.push_back(move);
		//sch.moveCommand->init(&s, MovementDirection::LEFT, deltaTime, MOVELEFT);
		//s.inputQueue.push_back(sch.moveCommand);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 25))
	{
		MoveCommand* move = new MoveCommand();
		move->init(&s, RIGHT, deltaTime, MOVERIGHT);
		s.inputQueue.push_back(move);
		//sch.moveCommand->init(&s, MovementDirection::RIGHT, deltaTime, MOVERIGHT);
		//s.inputQueue.push_back(sch.moveCommand);
	}
	else if(s.vel.x != 0)
	{
		MoveCommand* move = new MoveCommand();
		move->init(&s, STILL, deltaTime, NO_MOVE);
		s.inputQueue.push_back(move);
	}

	//utility[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	
	s.running = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::getAxisPosition(0, sf::Joystick::Z) > 25;
	utility[1] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0)) && !utility[1] ? true : false;
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0)) && !utility[1])
	{
		if(s.isHanging)
		{
			s.inputQueue.push_back(new ClimbCommand(&s, CLIMB));
		}
		else
		{
			JumpCommand* jump = new JumpCommand(&s, JUMP);
			s.inputQueue.push_back(jump);
		}
	}
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
	//std::cout << "Z axis: " << sf::Joystick::getAxisPosition(0, sf::Joystick::Z) << std::endl;
	utility[2] = grappleReset && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Joystick::getAxisPosition(0, sf::Joystick::Z) < -0.1)) && !utility[2] ? true : false;

	grappleReset = (sf::Joystick::getAxisPosition(0, sf::Joystick::Z) > -10 && sf::Joystick::getAxisPosition(0, sf::Joystick::Z) < 10);
	//utility[3] = (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 2)) && !utility[3] ? true : false;
	utility[4] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::isButtonPressed(0, 3)) && !utility[4] ? true : false;
	utility[5] = (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -50) && !utility[6] ? true : false;
	utility[6] = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50) && !utility[5] ? true : false;

	playerMove(s, deltaTime);
	viewMove(camera, s, deltaTime);

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
/*	if(movement[0])
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
		player.horizontalAcceleration(STILL, deltaTime);*/

	if(utility[1])
	{
		//if(!player.isHanging && !player.isFalling)
			//player.jump();
		/*else if(player.isHanging && !player.isVaulting)
		{
			player.interpolateVaultAboveGrappleTile();
			//s.instantVaultAboveGrappleTile();
		}*/
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
						//player.grapple();
						GrappleCommand* grapple = new GrappleCommand(&player, GRAPPLE);
						player.inputQueue.push_back(grapple);

						currentGrappleCooldown = 0;
					}
					else
						player.currentCooldown += deltaTime;
				}
				else if(!player.isVaulting)
				{
					player.isHanging = false;
					player.hShot.isDisabled = true;

					delete player.currentState;
					player.currentState = new JumpingState();
					player.isFalling = true;

					//player.inputQueue.push_back(new ClimbCommand(&player, CLIMB));
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

void InputManager::viewMove(Camera* camera, Player& s, float deltaTime)
{
	
	viewDifference = 100.0f*deltaTime;	
	if(s.vel.x == 0 && s.vel.y == 0 && !s.grappleInProgress)
	{
		if(utility[5])
		{
			s.updateUI(camera->viewMove(true, deltaTime));
		}
		else if(utility[6])
		{
			s.updateUI(camera->viewMove(false, deltaTime));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
		{
			viewChangedY = rand() % 50;
			viewChangedX = rand() % 50;
			camera->shakeScreen(viewChangedX, viewChangedY);
			s.updateUI(sf::Vector2f(viewChangedX, viewChangedY));
		}
		else
		{
			camera->viewReset();
			camera->endMovement();
		}

		//std::cout << viewChanged << std::endl;
		//std::cout << Global::GetInstance().yOffset << std::endl;
	}
	else
	{
		Global::GetInstance().topLeft.y -= viewChangedY;
		viewChangedY = 0;
	}
}