#pragma once

#include "BaseObject.h"
#include "Events.h"


class Observer
{
public: 
	virtual ~Observer() {}
	virtual void onNotify(const BaseObject& entity, Util::Events e) = 0;
};
