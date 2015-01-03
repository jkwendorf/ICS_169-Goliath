#pragma once

#include "Observer.h"

template<class Entity>

class PlayerInventory : public Observer<Entity>
{
public:
	static PlayerInventory& GetInstance()
	{
		static PlayerInventory instance;
		return instance;
	}

	PlayerInventory(int slots);
	void onNotify(const Entity& entity, Event event)
	void updateInventory(int slotToUpdate, int numberToAdd);
private:
	int* PlayerInventory;
};