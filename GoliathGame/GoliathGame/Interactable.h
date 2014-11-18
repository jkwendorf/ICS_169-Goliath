#pragma once

#include "BaseObject.h"

class Interactable
{
private:
	int level, section;

	Interactable();
public:
	Interactable(int level, int section);
	~Interactable();
	int getLevel();
	int getSection();

};