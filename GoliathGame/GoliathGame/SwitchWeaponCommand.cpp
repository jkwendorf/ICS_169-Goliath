#include "SwitchWeaponCommand.h"

SwitchWeaponCommand::SwitchWeaponCommand(Player* player_, Input inputCode_)
	:player(player_)
{
	inputCode = inputCode_;
}

void SwitchWeaponCommand::execute()
{
	player->weapon==SWORD ? player->weapon=CROSSBOW : player->weapon=SWORD;
}