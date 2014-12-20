#include "Player.h"
#include "Global.h"
#include "PhysicsManager.h"

Player::Player() 
	: BaseObject(), grappleInProgress(false), facingRight(true),running(false), isVaulting(false), 
	isHanging(false), shouldHang(false), health(Global::GetInstance().basePlayerStats[0]), 
	stamina(Global::GetInstance().basePlayerStats[1]),	weaponCooldown(Global::GetInstance().basePlayerStats[4])
{
	vel = sf::Vector2f(0.0,0.0);

	sprite.setTexture(*TextureManager::GetInstance().retrieveTexture("David"));
	//sprite.setPosition(64, 560);
	sprite.setPosition(150, 64);
	sprite.setScale( (PLAYER_DIM_X / (float)sprite.getTexture()->getSize().x), (PLAYER_DIM_Y / (float)sprite.getTexture()->getSize().y));
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
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

Player::~Player() 
{
	delete ui;
}

void Player::update(float deltaTime)
{
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
		hShot.update(deltaTime);
		if(sqrt(pow((std::abs(hShot.sprite.getPosition().x - sprite.getPosition().x)),2) + 
			pow((std::abs(hShot.sprite.getPosition().y - sprite.getPosition().y)),2)) >= 300)
		{
			hShot.grappleInProgress = false;
			hShot.hookedOnSomething = false;
		}
	}

	if((!hShot.hookedOnSomething || !hShot.grappleInProgress) && !isHanging)
	{	
		// Move the player
		verticalAcceleration(deltaTime);
		move(vel*deltaTime);
	}
	else if(hShot.grappleInProgress && hShot.hookedOnSomething)
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
	else if(isHanging && isVaulting)
	{
		if(sprite.getPosition().y > vaultPos.y)
		{
			move(0.f, -300.f*deltaTime);

			if(sprite.getPosition().y <= vaultPos.y)
				sprite.setPosition(sprite.getPosition().x, vaultPos.y);
		}
		else if(sprite.getPosition().y == vaultPos.y)
		{
			if(hShot.fireRight)
			{
				move(300.f*deltaTime, 0.f);

				if(sprite.getPosition().x >= vaultPos.x)
					sprite.setPosition(vaultPos.x, sprite.getPosition().y);
			}
			else
			{
				move(-300.f*deltaTime, 0.f);
				
				if(sprite.getPosition().x <= vaultPos.x)
					sprite.setPosition(vaultPos.x, sprite.getPosition().y);
			}
		}

		if(vaultPos == sprite.getPosition())
		{
			isHanging = false;
			isVaulting = false;
		}
	}

	for(int x = 0; x < 3; x++)
	{
		if(!ammo[x].moving)
			ammo[x].setLocation(sf::Vector2f(sprite.getPosition().x + 125, sprite.getPosition().y + 25));
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
				soundEffects[SHOOT].play();
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
			soundEffects[ATTACK].play();
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

	/* //TESTING CIRCLE
	sf::CircleShape circle = sf::CircleShape(5.0);
	circle.setPosition(sprite.getPosition());
	circle.setFillColor(sf::Color::Red);
	window.draw(circle);
	*/
}

void Player::grapple()
{
	if(!hShot.grappleInProgress && !isVaulting)
	{
		soundEffects[HOOK].play();
		hShot.grappleInProgress = true;
	
		if(facingRight)
		{
			hShot.startLocation = sf::Vector2f(sprite.getPosition().x + 60, sprite.getPosition().y - 15);
			hShot.grappleToLocation(sf::Vector2f(sprite.getPosition().x + 300 , sprite.getPosition().y - 175));
		}
		else
		{
			hShot.startLocation = sf::Vector2f(sprite.getPosition().x - 60, sprite.getPosition().y - 15);
			hShot.grappleToLocation(sf::Vector2f(sprite.getPosition().x - 300 , sprite.getPosition().y - 175));
		}
		hShot.fireRight = facingRight;
	}
}

void Player::resetPosition(sf::Vector2f& newPos)
{
	sprite.setPosition(newPos);
}

void Player::jump()
{
	soundEffects[JUMP].play();
	vel.y = JUMP_SPEED;
	isFalling = true;
}

void Player::playerUpdate(sf::View* view, sf::Vector2i roomSize, float deltaTime)
{
	viewCheck(view, roomSize.x, roomSize.y);
	update(deltaTime);
}

void Player::viewCheck(sf::View* view, int width, int height)
{
	if(facingRight)
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
	}

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

	if(sprite.getPosition().y - (PLAYER_DIM_Y / 2) < 0 + Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = sprite.getPosition().y - (PLAYER_DIM_Y / 2) - Global::GetInstance().yOffset;
		atTopEdge = true;
		atBottomEdge = false;
	}
	else if(sprite.getPosition().y + (PLAYER_DIM_Y / 2) > SCREEN_HEIGHT - Global::GetInstance().yOffset)
	{
		Global::GetInstance().topLeft.y = sprite.getPosition().y + (PLAYER_DIM_Y / 2) + Global::GetInstance().yOffset - SCREEN_HEIGHT;
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
			float maxSpeed = SPEED;
			if(dir == LEFT)
			{ 
				maxSpeed = -1.f*maxSpeed;
				if(running && stamina > 0)
				{
					maxSpeed -= BOOST;
					vel.x += (MOVE_ACCEL+BOOST)*dir*deltaTime;
				}
				else
					vel.x += MOVE_ACCEL*dir*deltaTime;

				vel.x = max(vel.x, maxSpeed);
			}
			else
			{
				if(running && stamina > 0)
				{
					maxSpeed += BOOST;
					vel.x += (MOVE_ACCEL+BOOST)*dir*deltaTime;
				}
				else
					vel.x += MOVE_ACCEL*dir*deltaTime;

				vel.x = min(vel.x, maxSpeed);
			}
		}
		else
		{
			if(vel.x > 0.f)
			{
				vel.x -= MOVE_ACCEL*deltaTime;
				if(vel.x <= 0.f)
					vel.x = 0.f;
			}
			else if(vel.x < 0.f)
			{
				vel.x += MOVE_ACCEL*deltaTime;
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
		if(vel.y >= TERMINAL_VELOCITY)
			vel.y = TERMINAL_VELOCITY;
		else
			vel.y += GRAVITY * deltaTime;
	}
}

void Player::moveOutOfTile(Tile t)
{
	float left = (sprite.getPosition().x + sprite.getGlobalBounds().width/2) - t.left, 
		right = (t.left + t.width) - (sprite.getPosition().x - sprite.getGlobalBounds().width/2), 
		up = (sprite.getPosition().y + sprite.getGlobalBounds().height/2) - t.top, 
		down = (t.top + t.height) - (sprite.getPosition().y - sprite.getGlobalBounds().height/2);

	float mini = min(up, down);
	mini = min(right, mini); 
	mini = min(left, mini);
	
	if(mini == left || mini == right)
		move(moveOutOfTileHorizontally(*this, t));
	else
		move(moveOutOfTileVertically(*this, t));
}

void Player::drawUI(sf::RenderWindow& window)
{
	ui->draw(window);
}

void Player::SetUpAugments()
{
	Global g= Global::GetInstance();
	int i = 0;
	for(auto& aug : g.augments)
	{
		//std::cout << health << "," << stamina << "," << playerSword.damage << "," << ammo[0].damage << "," << weaponCooldown << std::endl;
		health += aug[0] * g.PlayerInventory[i];
		//std::cout << "health " <<  aug[0] << "," << g.PlayerInventory[i] << std::endl;
		stamina += aug[1] * g.PlayerInventory[i];
		//std::cout << "stamina " <<  aug[1] << std::endl;
		playerSword.damage += aug[2] * g.PlayerInventory[i];
		//std::cout << "Sword " <<  aug[2] << std::endl;
		for(int x = 0; x < 3; x++)
		{
			ammo[x].damage += aug[3] * g.PlayerInventory[i];
			//std::cout << "Shooting " <<  aug[3] << std::endl;
		}
		weaponCooldown += aug[4] * g.PlayerInventory[i];
		//std::cout << "Speed " <<  aug[4] << std::endl;
		//std::cout << health << "," << stamina << "," << playerSword.damage << "," << ammo[0].damage << "," << weaponCooldown << std::endl;
		i++;
	}
	

}

void Player::SetUpEffects()
{
	soundEffects[ATTACK] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerAttack")));
	soundEffects[JUMP] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerJump")));
	soundEffects[SHOOT] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerShoot")));
	soundEffects[TAKEDMG] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerTakeDMG")));
	soundEffects[HOOK] = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("playerHook")));
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
	if(hShot.fireRight)
		vaultPos = sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width/2 + GAME_TILE_DIM/2, 
								sprite.getPosition().y - sprite.getGlobalBounds().height);
	else
		vaultPos = sf::Vector2f(sprite.getPosition().x - sprite.getGlobalBounds().width/2 - GAME_TILE_DIM/2, 
								sprite.getPosition().y - sprite.getGlobalBounds().height);

	isVaulting = true;
}