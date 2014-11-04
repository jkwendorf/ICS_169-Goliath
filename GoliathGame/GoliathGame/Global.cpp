#include "Global.h"

Global::Global()
{
}

Global::~Global()
{

}

void Global::setScreenSize(int w, int h)
{
	screenHeight = h;
	screenWidth = w;
}

void Global::setFPS(int f)
{
	fps = f;
}

void Global::calculateOffset()
{
	
}