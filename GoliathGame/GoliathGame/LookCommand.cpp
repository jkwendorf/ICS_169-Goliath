#include "LookCommand.h"


LookCommand::LookCommand(Player* player_, sf::View* view_, float deltaTime_, LookDirection direction_)
	:player(player_), view(view_), deltaTime(deltaTime_), dir(direction_)
{
}

void LookCommand::execute()
{
	player->viewMove(view, deltaTime, dir);
}
