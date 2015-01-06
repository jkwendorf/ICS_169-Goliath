#include "AttackCommand.h"

AttackCommand::AttackCommand(Player* player_)
	:player(player_)
{
}

void AttackCommand::execute()
{
	player->attack();
}