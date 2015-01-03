#pragma once

#include "Observer.h"
#include <iterator>
#include "BaseObject.h"
#include "AudioManager.h"

class PlayerInventory : public Observer
{
public:
	PlayerInventory();
	~PlayerInventory();
	void addItem(const std::string& itemName, int amount);
	void onNotify(const BaseObject& entity, Util::Events e);
	void updateInventory(const std::string& slotToUpdate, int numberToAdd);
	int checkInventory(const std::string& item);
private:
	std::map<std::string, int> inventory;
	sf::Sound gainItem;
};