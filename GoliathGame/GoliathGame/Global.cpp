#include "Global.h"

Global::Global()
{
}

Global::~Global()
{

}

void Global::setScreenSize(int w, int h)
{
	y = h;
	x = w;
	calculateOffset();
}

void Global::setFPS(int f)
{
	fps = f;
}

void Global::calculateOffset()
{
	//grab height and width and calculate that offset
}