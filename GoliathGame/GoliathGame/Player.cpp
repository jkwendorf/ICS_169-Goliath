#include "Player.h"
#include "Global.h"
#include "PhysicsManager.h"
#include "IdleState.h"
#include "VaultingState.h"

Player::Player() 
	: BaseObject(0), grappleInProgress(false), facingRight(true),running(false), isVaulting(false), 
	isHanging(false), shouldHang(false), health(Global::GetInstance().basePlayerStats[0]), 
	stamina(Global::GetInstance().basePlayerStats[1]),	weaponCooldown(Global::GetInstance().basePlayerStats[4]), bottomPoint(0),
	deathTimer(0.0f), currentState(nullptr), collidingLeft(false), collidingRight(false)
{
	vel = sf::Vector2f(0.0,0.0);

	jumpSpeed = Global::GetInstance().playerAttributes[1];
	moveSpeed = Global::GetInstance().playerAttributes[0];
	moveAccel = Global::GetInstance().playerAttributes[2];
	boostSpeed = Global::GetInstance().playerAttributes[3];
	grappleSpeed = Global::GetInstance().playerAttributes[4];
	gravity = Global::GetInstance().playerAttributes[5];
	fallSpeed = Global::GetInstance().playerAttributes[6];
	player = Animation(4, 4, 90, 120, .10); 
	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("David_Run2"));
	crosshair.setTexture(*TextureManager::GetInstance().retrieveTexture("crosshair"));
	crosshair.setPosition(-1000,-1000);
	//crosshair.setScale(1.2,1.2);
	//sprite.setPosition(64, 560);
	//sprite.setPosition(500, 64);
	sprite.setScale(.5,.5);
	sprite.setOrigin(45,60);
	sprite.setTextureRect(sf::IntRect(0, 0, 90,120));
	
	sprite.setScale( (GAME_TILE_DIM / 90.0f), 1);
	weapon = SWORD;

	isFalling = true;
	for(int x = 0; x < 3; x++)
	{
		ammo[x] = Projectile(sprite.getPosition(), sf::Vector2f(0.0,0.0));
		//ammo[x].sprite.setColor(sf::Color(x*50 + 150, 0, 0));
		ammo[x].damage = Global::GetInstance().basePlayerStats[3];
	}
	grappleDir.y = 100;
	playerSword.damage = Global::GetInstance().basePlayerStats[2];

	SetUpAugments();

	ui = new UserInterface(health, stamina);
	SetUpEffects();
}

void Player::init(CollisionManager* collisionManager_, BaseState* startState)
{
	if(currentState != nullptr)
		delete currentState;
	collisionManager = collisionManager_;
	currentState = startState;
}

Player::~Player() 
{
	delete ui;
	delete currentState;
}

void Player::handleInput()
{
	for(std::deque<Command*>::iterator it = inputQueue.begin(); it != inputQueue.end(); it++)
	{

		//std::cout << inputQueue.size() << std::endl;
		currentState->handleInput(this, *it);
		if(newState != NULL)
		{
			delete currentState;
			currentState = newState;
			newState = NULL;
		}
	}
	while(!inputQueue.empty())
	{
		delete inputQueue.front();
		inputQueue.pop_front();
	}
}

void Player::update(float deltaTime)
{

	if(deathTimer > 0)
	{
		deathTimer -= deltaTime;
	}

	currentState->update(this, deltaTime);
	//std::cout << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
	/*
	while(!inputQueue.empty())
	//if(inputQueue.empty())
		currentState->update(this, deltaTime);
	/*else
	{
		while(!inputQueue.empty())
		{
			//currentState->update(inputQueue.front(), deltaTime);
			currentState->update(this, deltaTime);
			delete inputQueue.front();
			inputQueue.pop_front();
		}
	}*/
	
	hShot.update(deltaTime);
	//std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
	if(!hShot.grappleInProgress)
	{
		if(facingRight)
			hShot.update(sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y - 15));
		else
			hShot.update(sf::Vector2f(sprite.getPosition().x - 60, sprite.getPosition().y - 15));
	}
	else
	{
		//hShot.update(deltaTime);
		if(sqrt(pow((std::abs(hShot.sprite.getPosition().x - sprite.getPosition().x)),2) + 
			pow((std::abs(hShot.sprite.getPosition().y - sprite.getPosition().y)),2)) >= hShot.grappleLength || hShot.currentCooldown >= hShot.weaponCooldown)
		{
			hShot.grappleInProgress = false;
			hShot.hookedOnSomething = false;			
		}
	}

	/*if(hShot.grappleInProgress && hShot.hookedOnSomething)
	{
		vel.x = 0.f;
		vel.y = 0.f;
		// If the direction isn't set, set it
		direction(hShot.grappleLocation, sprite.getPosition(), grappleDir);
		// Move to the point and do stuff
		grappleHookMove(*this, deltaTime);

		// If were at the point, end grappling and reset the direction
		if(hShot.grappleLocation == sprite.getPosition())
		{
				hShot.hookedOnSomething = false;
				hShot.grappleInProgress = false;
				isFalling = true;
				grappleDir.y = 100;
			
			if(shouldHang)
			{
// JW: We should make it so the InputManager can tell us if a key is down at any point.
				shouldHang = false;
				isHanging = true;
				if(sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Joystick::isButtonPressed(0, 1))
				{
					interpolateVaultAboveGrappleTile();
				}
			}
		}
	}
	else */

	for(int x = 0; x < 3; x++)
	{
		if(!ammo[x].moving)
			ammo[x].setLocation(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 25));
		ammo[x].update(deltaTime);
	}
	
	if(!running && !playerSword.attacking)
		stamina++;
	if(stamina < 0)
		stamina = 0;
	if(stamina > 50)
		stamina = 50;
	if(health < 0)
		health = 0;
	if(health > 100)
		health = 100;

	playerSword.update(deltaTime);
	if(playerSword.attacking)
	{
		if(facingRight)
			playerSword.hitBox.setPosition(sprite.getPosition().x + PLAYER_DIM_X*1.5, sprite.getPosition().y);
		else
			playerSword.hitBox.setPosition(sprite.getPosition().x - PLAYER_DIM_X*1.5, sprite.getPosition().y);
	}
	ui->update(health, stamina);
	
	//Check for nearest grappleTile
	if(!collisionManager->isGrappleListEmpty())
	{
		closestGrappleTile = collisionManager->getNearestGrappleTile(*this);
		crosshair.setPosition(closestGrappleTile.left - 17, closestGrappleTile.top - 17);
		crosshair.setColor(sf::Color(crosshair.getColor().r, crosshair.getColor().g,crosshair.getColor().b, crosshair.getColor().a - 10));
		if(crosshair.getColor().a < 0)
			crosshair.setColor(sf::Color(crosshair.getColor().r, crosshair.getColor().g,crosshair.getColor().b, 255));
	}
	else
		crosshair.setPosition(-1000,-1000);


	//Animated sprite update
	player.update(deltaTime, sprite, 1, facingRight);

}

void Player::takeDamage()
{
	//Player health decrease
	if(deathTimer <= 0)
	{
		deathTimer = 1.0f;
		health -= 100;
		std::cout << "Its a trap!" << std::endl;
		return;
	}
	std::cout << "Not taking damage" << std::endl;

}

void Player::attack()
{

	if(weapon == CROSSBOW)
	{
		
		float xSpeed;
		for(int x = 0; x < 3; x++)
			if(!ammo[x].moving)
			{
				if(facingRight)
					xSpeed = 10.0;
				else
					xSpeed = -10.0;
				
				ammo[x].setVelocity(sf::Vector2f(xSpeed,0.0));
				ammo[x].moving = true;
				soundEffects[SHOOTSOUND].play();
				break;
			}

		
		if(ammo[0].velocity.x == 0)
			ammo[0].velocity.x ? facingRight =  10.0 : -10.0;
		else if(ammo[1].velocity.x == 0)
			ammo[1].velocity.x ? facingRight =  10.0 : -10.0;
		else if(ammo[2].velocity.x == 0)
			ammo[2].velocity.x ? facingRight =  10.0 : -10.0;
		
	}
	else if (weapon == SWORD)
	{
		if(stamina > 10)
		{
			if(facingRight)
				playerSword.hitBox.setPosition(sprite.getPosition().x + PLAYER_DIM_X*1.5, sprite.getPosition().y);
			else
				playerSword.hitBox.setPosition(sprite.getPosition().x - PLAYER_DIM_X*1.5, sprite.getPosition().y);
			soundEffects[ATTACKSOUND].play();
			playerSword.attacking = true;
		}
		stamina -= 10;
		playerSword.currentCooldown = 0.0;
	}
}

void Player::move(float x, float y)
{
	sprite.move(x, y);
}

void Player::move(sf::Vector2f& distance)
{
	sprite.move(distance);
}

void Player::draw(sf::RenderWindow& window)
{
	//ui->draw(window);
	BaseObject::draw(window);
	window.draw(hShot.sprite);
	playerSword.draw(window);
	for(int x = 0; x < 3; x++)
		if(ammo[x].moving)
			ammo[x].draw(window);
	
	window.draw(crosshair);
	rectangle = sf::RectangleShape(sf::Vector2f(36, 36));
	rectangle.setPosition(sprite.getPosition().x - 20, sprite.getPosition().y - 40);
	rectangle.setFillColor(sf::Color::Blue);
	window.draw(rectangle);
	
	/* //TESTING CIRCLE
	sf::CircleShape circle = sf::CircleShape(5.0);
	circle.setPosition(sprite.getPosition());
	circle.setFillColor(sf::Color::Red);
	window.draw(circle);
	*/
}

void Player::grapple()
{
	if(!collisionManager->isGrappleListEmpty())
	{
		if(!hShot.grappleInProgress && !isVaulting)
		{
			soundEffects[HOOKSOUND].play();
			hShot.grappleInProgress = true;
			std::cout << closestGrappleTile.top << " " << closestGrappleTile.left << std::endl;
			if(facingRight)
			{
				hShot.startLocation = sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y - 15);
				hShot.grappleToLocation(sf::Vector2f(closestGrappleTile.left + closestGrappleTile.width/2 , closestGrappleTile.top + closestGrappleTile.height/2));
			}
			else
			{
				hShot.startLocation = sf::Vector2f(sprite.getPosition().x - 60, sprite.getPosition().y - 15);
				hShot.grappleToLocation(sf::Vector2f(closestGrappleTile.left + closestGrappleTile.width/2 , closestGrappleTile.top + closestGrappleTile.height/2));
			}
			hShot.fireRight = facingRight;
			
		}
	}
}

void Player::resetPosition(sf::Vector2f& newPos)
{
	sprite.setPosition(newPos);
	vel.x = 0;
}

void Player::jump()
{
	if(!isHanging && !isFalling)
	{
		soundEffects[JUMPSOUND].play();
 		vel.y = jumpSpeed;
		isFalling = true;
	}
}

void Player::playerUpdate(sf::View* view, sf::Vector2i roomSize, float deltaTime)
{
	viewCheck(view, roomSize.x, roomSize.y);
	update(deltaTime);
}

void Player::viewCheck(sf::View* view, int width, int height)
{
	/*if(facingRight)
	{
		if(sprite.getPosition().x > SCREEN_WIDTH - Global::GetInstance().xOffset + Global::GetInstance().topLeft.x)
		{
			Global::GetInstance().topLeft.x = sprite.getPosition().x - SCREEN_WIDTH + Global::GetInstance().xOffset;
		}
	}
	else
	{
		if(sprite.getPosition().x < Global::GetInstance().topLeft.x + Global::GetInstance().xOffset)
		{
			Global::GetInstance().topLeft.x = sprite.getPosition().x - Global::GetInstance().xOffset;
		}
	}*/

	Global::GetInstance().topLeft.x = sprite.getPosition().x - Global::GetInstance().xOffset;

	if(Global::GetInstance().topLeft.x < 0)
	{
		Global::GetInstance().topLeft.x = 0;
	}

	if(width - Global::GetInstance().xOffset < sprite.getPosition().x)
	{
		Global::GetInstance().topLeft.x = width - SCREEN_WIDTH;
		if(width % SCREEN_WIDTH > 0)
		{
			Global::GetInstance().topLeft.x = (width / SCREEN_WIDTH) * SCREEN_WIDTH
				- SCREEN_WIDTH + (width % SCREEN_WIDTH);
		}
	}

	//If falling, bottom edge is player position
	//If not, bottom edge is player's bottom most point
	//Highest bottom point is TBD

	if(isFalling)
	{
		bottomPoint = sprite.getPosition().y - (PLAYER_DIM_Y / 2);
		//std::cout << bottomPoint << std::endl;
	}

	if(sprite.getPosition().y - (PLAYER_DIM_Y / 2) < 0 + Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = sprite.getPosition().y - (PLAYER_DIM_Y / 2) - Global::GetInstance().yOffset;
		atTopEdge = true;
		atBottomEdge = false;
	}
	else if(sprite.getPosition().y - (PLAYER_DIM_Y / 2) > SCREEN_HEIGHT - Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = sprite.getPosition().y - (PLAYER_DIM_Y / 2) + Global::GetInstance().yOffset - SCREEN_HEIGHT;
		atTopEdge = false;
		atBottomEdge = true;
	}
	else
	{
		atTopEdge = false;
		atBottomEdge = false;
	}

	if(Global::GetInstance().topLeft.y > height - SCREEN_HEIGHT)
	{
		Global::GetInstance().topLeft.y = height - SCREEN_HEIGHT;
		atTheBottom = true;
	}
	else
	{
		atTheBottom = false;
	}
		
	if(Global::GetInstance().topLeft.x == 0)
	{
		if((sprite.getPosition().x - (PLAYER_DIM_X / 2)) < 0)
		{
			sprite.setPosition((0 + PLAYER_DIM_X /2), sprite.getPosition().y);
			vel.x = 0.f;
		}
		else if((sprite.getPosition().x + (PLAYER_DIM_X / 2)) > (width - 1))
		{
			sprite.setPosition((width - 1 - (PLAYER_DIM_X / 2)), sprite.getPosition().y);
			vel.x = 0.f;
		}
	}
	else if(Global::GetInstance().topLeft.x == (width - SCREEN_WIDTH))
	{
		if((sprite.getPosition().x + (PLAYER_DIM_X / 2)) > (width - 1))
		{
      		sprite.setPosition((width - 1 - (PLAYER_DIM_X / 2)), sprite.getPosition().y);
			vel.x = 0.f;
		}
	}

	view->reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void Player::horizontalAcceleration(MovementDirection dir, float& deltaTime)
{

	if(!hShot.hookedOnSomething || !hShot.grappleInProgress)
	{
		if(dir != STILL)
		{
			float maxSpeed = moveSpeed;
			if(dir == LEFT)
			{ 
				if(!collidingLeft)
				{
					maxSpeed = -1.f*maxSpeed;
					
					if(vel.x <= 0)
					{
						if(running && stamina > 0)
						{
							maxSpeed -= boostSpeed;
							vel.x += (moveAccel+boostSpeed)*dir*deltaTime;
						}
						else
							vel.x += moveAccel*dir*deltaTime;
					}
					else
					{
						if(isFalling)
						{
							maxSpeed *= 0.75;
							vel.x += 0.75*(moveAccel)*dir*deltaTime;
						}
						else if(running && stamina > 0)
						{
							maxSpeed -= boostSpeed;
							vel.x += 3*(moveAccel+boostSpeed)*dir*deltaTime;
						}
						else
							vel.x += 3*moveAccel*dir*deltaTime;	
					}

					vel.x = max(vel.x, maxSpeed);

					if(collidingRight)
						collidingRight = false;
				}
			}
			else
			{
				if(!collidingRight)
				{
					if(vel.x >= 0)
					{
						if(isFalling)
						{
							maxSpeed *= 0.75;
							vel.x += 0.75*(moveAccel)*dir*deltaTime;
						}
						else if(running && stamina > 0)
						{
							maxSpeed += boostSpeed;
							vel.x += (moveAccel+boostSpeed)*dir*deltaTime;
						}
						else
							vel.x += moveAccel*dir*deltaTime;
					}
					else
					{
						if(running && stamina > 0)
						{
							maxSpeed += boostSpeed;
							vel.x += 3*(moveAccel+boostSpeed)*dir*deltaTime;
						}
						else
							vel.x += 3*moveAccel*dir*deltaTime;					
					}

					vel.x = min(vel.x, maxSpeed);

					if(collidingLeft)
						collidingLeft = false;
				}
			}
		}
		else
		{
			if(vel.x > 0.f)
			{
				if(isFalling)
					vel.x -= 0.75*moveAccel*deltaTime;
				else
					vel.x -= 2*moveAccel*deltaTime;

				if(vel.x <= 0.f)
					vel.x = 0.f;
			}
			else if(vel.x < 0.f)
			{
				if(isFalling)
					vel.x += 0.75*moveAccel*deltaTime;
				else
					vel.x += 2*moveAccel*deltaTime;

				if(vel.x >= 0.f)
					vel.x = 0.f;
			}
		}
	}
}

void Player::verticalAcceleration(float& deltaTime)
{
	if(isFalling && !isHanging)
	{
		if(vel.y >= fallSpeed)
			vel.y = fallSpeed;
		else
			vel.y += gravity * deltaTime;
	}
}

/*void Player::moveOutOfTile(Tile* t)
{
	float left = (sprite.getPosition().x + sprite.getGlobalBounds().width/2) - t->left, 
		right = (t->left + t->width) - (sprite.getPosition().x - sprite.getGlobalBounds().width/2), 
		up = (sprite.getPosition().y + sprite.getGlobalBounds().height/2 + 0.1f) - t->top, 
		down = (t->top + t->height) - (sprite.getPosition().y - sprite.getGlobalBounds().height/2); 

	float mini = min(up, down);
	mini = min(right, mini); 
	mini = min(left, mini);

	if(mini == left || mini == right)
		move(moveOutOfTileHorizontally(*this, t));
	else
	{
		move(moveOutOfTileVertically(*this, t));

		if(!isFalling)
		{
			delete currentState;
			//currentState = new IdleState();
			currentState = new OnGroundState();
		}
	}
}*/

void Player::moveOutOfTile(Tile* t)
{
	float left = (sprite.getPosition().x + sprite.getGlobalBounds().width/2) - t->left, 
		right = (t->left + t->width) - (sprite.getPosition().x - sprite.getGlobalBounds().width/2), 
		up = (sprite.getPosition().y + sprite.getGlobalBounds().height/2.f + 0.1f) - t->top, 
		down = (t->top + t->height) - (sprite.getPosition().y - sprite.getGlobalBounds().height/2); 

	float mini = min(up, down);
	mini = min(right, mini); 
	mini = min(left, mini);

	if(mini == left)
	{
		move(sf::Vector2f(-left, 0.f));

		if(!collisionManager->playerCollisionDetection(this))
		{
			vel.x = 0;
			collidingRight = true;
		}
	}
	else if (mini == right)
	{
		move(sf::Vector2f(right, 0.f));

		if(!collisionManager->playerCollisionDetection(this))
		{
			vel.x = 0;
			collidingLeft = true;
		}
	}
	else if(mini == up)
	{
		move(sf::Vector2f(0.f, -up));

		if(vel.y >= 0)
		{
			if(!collisionManager->playerCollisionDetection(this))
			{
				vel.y = 0;
				isFalling = false;
				delete currentState;
				currentState = new OnGroundState();
			}
		}
	}
	else
	{
		move(sf::Vector2f(0.f, down));
		
		if(!collisionManager->playerCollisionDetection(this))
		{
			vel.y = 0;
		}
	}
}

void Player::viewMove(float deltaTime, float& viewChanged_, LookDirection dir)
{
	float viewDifference = 100.0f*deltaTime;	
	if(dir == UP)
	{
		viewChanged_ -= viewDifference;
		if(viewChanged_ < Global::GetInstance().yOffset * (-4) && viewChanged_ < 0)
		{
			viewDifference = 0;
			viewChanged_ = Global::GetInstance().yOffset * -4;
		}
		Global::GetInstance().topLeft.y -= viewDifference;
		if(atBottomEdge)
		{
			view->reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y + viewChanged_, SCREEN_WIDTH, SCREEN_HEIGHT));
			ui->updateDifferent(health, stamina, Global::GetInstance().topLeft.y + viewChanged_);
		}
	}
	else
	{
		viewChanged_ += viewDifference;
		if(viewChanged_ > Global::GetInstance().yOffset * 4 && viewChanged_ > 0)
		{
			viewDifference = 0;
			viewChanged_ = Global::GetInstance().yOffset * 4;
		}
		Global::GetInstance().topLeft.y += viewDifference;
		if(atTopEdge || !atTheBottom)
		{
			view->reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y + viewChanged_, SCREEN_WIDTH, SCREEN_HEIGHT));
			ui->updateDifferent(health, stamina, Global::GetInstance().topLeft.y + viewChanged_);
		}
	}		

}

void Player::drawUI(sf::RenderWindow& window)
{
	ui->draw(window);
}

void Player::SetUpAugments()
{
	Global g = Global::GetInstance();
	
	int i = 0;
	
	for(auto& aug : g.augments)
	{
		int num = g.inventory->checkInventory(aug.first);
		//std::cout << health << "," << stamina << "," << playerSword.damage << "," << ammo[0].damage << "," << weaponCooldown << std::endl;
		health += aug.second[0] * num;
		//std::cout << "health " <<  aug[0] << "," << g.PlayerInventory[i] << std::endl;
		stamina += aug.second[1] * num;
		//std::cout << "stamina " <<  aug[1] << std::endl;
		playerSword.damage += aug.second[2] * num;
		//std::cout << "Sword " <<  aug[2] << std::endl;
		for(int x = 0; x < 3; x++)
		{
			ammo[x].damage += aug.second[3] * num;
			//std::cout << "Shooting " <<  aug[3] << std::endl;
		}
		weaponCooldown += aug.second[4] * num;
		//std::cout << "Speed " <<  aug[4] << std::endl;
		//std::cout << health << "," << stamina << "," << playerSword.damage << "," << ammo[0].damage << "," << weaponCooldown << std::endl;
		i++;
	}
}

void Player::SetUpEffects()
{
	soundEffects[ATTACKSOUND] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerAttack")));
	soundEffects[JUMPSOUND] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerJump")));
	soundEffects[SHOOTSOUND] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerShoot")));
	soundEffects[TAKEDMGSOUND] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerTakeDMG")));
	soundEffects[HOOKSOUND] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerHook")));
}

void Player::instantVaultAboveGrappleTile()
{
	if(hShot.fireRight)
		sprite.setPosition(sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width/2 + GAME_TILE_DIM/2, 
							sprite.getPosition().y - sprite.getGlobalBounds().height));
	else
		sprite.setPosition(sf::Vector2f(sprite.getPosition().x - sprite.getGlobalBounds().width/2 - GAME_TILE_DIM/2, 
							sprite.getPosition().y - sprite.getGlobalBounds().height));

	isHanging = false;
}

void Player::interpolateVaultAboveGrappleTile()
{
	if(!isVaulting)
	{
		if(hShot.fireRight)
			vaultPos = sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width/2 + GAME_TILE_DIM/2, 
									sprite.getPosition().y - sprite.getGlobalBounds().height);
		else
			vaultPos = sf::Vector2f(sprite.getPosition().x - sprite.getGlobalBounds().width/2 - GAME_TILE_DIM/2, 
									sprite.getPosition().y - sprite.getGlobalBounds().height);

		isVaulting = true;
		//currentState = new VaultingState();
		newState = new VaultingState();
	}
}

void Player::onNotify(const BaseObject& entity, Util::Events e)
{
	switch (e)
    {
	case Util::Events::TAKEDAMAGE:
		if (entity.objectNum == 0)
		{
			takeDamage();
		}
		break;
    }
}

bool Player::checkDead()
{
	if(health <= 0)
		return true;
	return false;
}

void Player::resetHealth()
{
	health = 100;
	ui->resetUI();
}