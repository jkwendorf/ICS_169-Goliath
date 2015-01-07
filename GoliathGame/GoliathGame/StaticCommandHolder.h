#pragma once 

#include "AttackCommand.h"
#include "ClimbCommand.h"
#include "GrappleCommand.h"
#include "JumpCommand.h"
#include "LookCommand.h"
#include "MoveCommand.h"
#include "RunCommand.h"
#include "SwitchWeaponCommand.h"

struct StaticCommandHolder
{
	static AttackCommand* attackcommand;
	static ClimbCommand* climbCommand;
	static GrappleCommand* grappleCommand;
	static JumpCommand* jumpCommand;
	static LookCommand* lookCommand;
	static MoveCommand* moveCommand;
	static RunCommand* runCommand;
	static SwitchWeaponCommand* switchwepCommand;
};