#pragma once

#include <SFML\Graphics.hpp>
#include "Global.h"

class Camera
{
public:
	Camera();
	~Camera();
	void setRoomSize(sf::Vector2f dim);
	void viewChange(sf::Vector2f playerPos);
	void viewReset();
	void viewMove(bool up, float deltaTime);
	sf::View getView();
	void setBottomPoint(float bot);
	void shakeScreen(float x, float y);

private:
	sf::Vector2f roomSize;
	sf::View view;
	float viewDifference, viewChangedY, viewChangedX;
	float bottomPoint;
};