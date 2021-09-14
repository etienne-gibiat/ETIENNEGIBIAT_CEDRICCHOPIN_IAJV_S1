#pragma once
#include <string>
#include "World.h"

class Action
{
public:
	Action(const std::string nameAction, World& world): myAction(nameAction), parWorld(world) {};
	void AddEffect(const std::string effect);
	void AddPrecondition(const std::string effect);

private:

	std::string myAction;
	World& parWorld;
};