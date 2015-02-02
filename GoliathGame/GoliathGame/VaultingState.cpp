#include "VaultingState.h"
#include "JumpingState.h" // JW: Probably should make a falling state

VaultingState::VaultingState()
{

}

void VaultingState::enter() 
{
}

void VaultingState::handleInput(Player* player, Command* input) 
{}

void VaultingState::update(Player* player, float deltaTime) 
{
	//if(player->isHanging && player->isVaulting)
	//{
	if(player->sprite.getPosition().y > player->vaultPos.y)
	{
		player->move(0.f, -300.f*deltaTime);

		if(player->sprite.getPosition().y <= player->vaultPos.y)
			player->sprite.setPosition(player->sprite.getPosition().x, player->vaultPos.y);
	}
	else if(player->sprite.getPosition().y == player->vaultPos.y)
	{
		if(player->hShot.fireRight)
		{
			player->move(300.f*deltaTime, 0.f);

			if(player->sprite.getPosition().x >= player->vaultPos.x)
				player->sprite.setPosition(player->vaultPos.x, player->sprite.getPosition().y);
		}
		else
		{
			player->move(-300.f*deltaTime, 0.f);
			
			if(player->sprite.getPosition().x <= player->vaultPos.x)
				player->sprite.setPosition(player->vaultPos.x, player->sprite.getPosition().y);
		}
	}
	if(player->vaultPos == player->sprite.getPosition())
	{
		player->isHanging = false;
		player->isVaulting = false;

		player->newState = new JumpingState();
	}
}

void VaultingState::exit() 
{
}