#pragma once 

#include "BaseState.h"
#include "IdleState.h"
#include "WalkingState.h"
#include "RunningState.h"
#include "JumpingState.h"
#include "GrapplingState.h"
#include "HangingState.h"
#include "AttackState.h"

struct StaticStateHolder
{
	StaticStateHolder()
	{
		idlestate = new IdleState();
		walkingState = new WalkingState();
		runningState = new RunningState();
		jumpingState = new JumpingState();
		grapplingState = new GrapplingState();
		hangingState = new HangingState();
	}
	~StaticStateHolder()
	{
		delete idlestate;
		delete walkingState;
		delete runningState;
		delete jumpingState;
		delete grapplingState;
		delete hangingState;
		delete attackState;
	}

	static IdleState* idlestate;
	static WalkingState* walkingState;
	static RunningState* runningState;
	static JumpingState* jumpingState;
	static GrapplingState* grapplingState;
	static HangingState* hangingState;
	static AttackState* attackState;
};
