#pragma once

#include <vector>
#include "Observer.h"


class Subject
{
private:
	std::vector<Observer*> observers;
	int numObservers;
public:
	virtual ~Subject() {};

	inline void addObserver(Observer* observer)
	{
		observers.push_back(observer);
	}

	inline void removeObserver(Observer* observer)
	{
		for(std::vector<Observer*>::iterator itr = observers.begin(); itr != observers.end(); itr++)
		{
			if(*itr == observer)
			{
				observers.erase(itr);
			}
		}
	}

	inline void notify(BaseObject& obj, Util::Events event)
	{
		for (int i = 0; i < observers.size(); i++)
		{
			observers[i]->onNotify(obj, event);
		}
	}
};