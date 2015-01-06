#include "SwitchWeaponCommand.h"

SwitchWeaponCommand::SwitchWeaponCommand(Player* player_)
	:player(player_)
{
}

void SwitchWeaponCommand::execute()
{
	player->weapon==SWORD ? player->weapon=CROSSBOW : player->weapon=SWORD;
}