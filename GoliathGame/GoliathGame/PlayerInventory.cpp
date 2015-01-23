#include "PlayerInventory.h"

PlayerInventory::PlayerInventory()
	:inventory()
{

	gainItem = sf::Sound(*AudioManager::GetInstance().retrieveSound(std::string("GainItem")));
}

PlayerInventory::~PlayerInventory()
{

}

void PlayerInventory::addItem(const std::string& itemName, int amount)
{
	inventory.insert(std::pair<std::string, int>(itemName, amount));
}

void PlayerInventory::onNotify(const BaseObject& entity, Util::Events event)
{
	switch (event)
    {
	case Util::Events::PICK_UP_ITEM:
		if (entity.objectNum == 0)
		{
			
			std::map<std::string, int>::iterator item = inventory.begin();
			int temp = std::rand() % inventory.size();
			std::cout << temp << std::endl;
			std::advance( item,  temp);
			updateInventory(item->first, 1); 
			gainItem.play();
		}
		break;
    }

}

void PlayerInventory::updateInventory(const std::string& slotToUpdate, int numberToAdd)
{
	inventory.at(slotToUpdate) += numberToAdd;
}

int PlayerInventory::checkInventory(const std::string& item)
{
	std::cout << inventory.at(0) << std::endl;
	int temp = 0;
	try
	{
		 temp = inventory.at(item);
	}
	catch(std::out_of_range e)
	{
		std::cout << e.what() << std::endl;
	}
	return temp;
}