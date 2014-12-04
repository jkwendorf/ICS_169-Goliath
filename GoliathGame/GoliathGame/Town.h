#pragma once 

#include "BaseGameScreen.h"
#include "Global.h"

class Town : public BaseGameScreen
{
public:
	Town();
	~Town();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void DeleteLevel();

private:
	int parts[];



};