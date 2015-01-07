#include "AttackCommand.h"

AttackCommand::AttackCommand(Player* player_, Input inputCode_)
	:player(player_)
{
	inputCode = inputCode_;
}

void AttackCommand::execute()
{
	player->attack();
}