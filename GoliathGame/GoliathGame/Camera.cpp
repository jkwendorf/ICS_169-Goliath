#include "Camera.h"

Camera::Camera() : viewDifference(0.0f), viewChangedX(0.0f), viewChangedY(0.0f), bottomPoint(0.0f)
{
	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
}

Camera::~Camera()
{

}

void Camera::setRoomSize(sf::Vector2f dim)
{
	roomSize = dim;
}

void Camera::viewChange(sf::Vector2f playerPos)
{
	Global::GetInstance().topLeft.x = playerPos.x - Global::GetInstance().xOffset;

	if(Global::GetInstance().topLeft.x < 0)
	{
		Global::GetInstance().topLeft.x = 0;
	}

	if(roomSize.x - Global::GetInstance().xOffset < playerPos.x)
	{
		int x = roomSize.x;
		Global::GetInstance().topLeft.x = roomSize.x - SCREEN_WIDTH;
	}

	Global::GetInstance().topLeft.y = playerPos.y - (PLAYER_DIM_Y / 2) + Global::GetInstance().yOffset - SCREEN_HEIGHT;

	//If falling, bottom edge is player position
	//If not, bottom edge is player's bottom most point
	//Highest bottom point is TBD

		Global::GetInstance().topLeft.y = playerPos.y - (PLAYER_DIM_Y / 2) + Global::GetInstance().yOffset - SCREEN_HEIGHT;

	if(Global::GetInstance().topLeft.y > roomSize.y - SCREEN_HEIGHT)
	{
		Global::GetInstance().topLeft.y = roomSize.y - SCREEN_HEIGHT;
	}

	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}

sf::Vector2f Camera::viewMove(bool up, float deltaTime)
{
	viewDifference = 100.0f * deltaTime;
	if(up)
	{
		viewChangedY -= viewDifference;

		if(viewChangedY < GAME_TILE_DIM * -5)
		{
			viewChangedY = GAME_TILE_DIM * -5;
		}
	}
	else
	{
		viewChangedY += viewDifference;

		if(viewChangedY > GAME_TILE_DIM * 5)
		{
			viewChangedY = GAME_TILE_DIM * 5;
		}

		if(Global::GetInstance().topLeft.y + viewChangedY > roomSize.y - SCREEN_HEIGHT)
		{
			viewChangedY -= viewDifference;
		}
	}

	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y + viewChangedY, SCREEN_WIDTH, SCREEN_HEIGHT));
	return sf::Vector2f(viewChangedX, viewChangedY);
}

void Camera::endMovement()
{
	viewDifference = 0;
	viewChangedY = 0;
	viewChangedX = 0;
}

void Camera::shakeScreen(float x, float y)
{
	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x + x, Global::GetInstance().topLeft.y + y, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void Camera::setBottomPoint(float bot)
{
	bottomPoint = bot;
}

void Camera::viewReset()
{
	view.reset(sf::FloatRect(Global::GetInstance().topLeft.x, Global::GetInstance().topLeft.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}

sf::View Camera::getView()
{
	return view;
}