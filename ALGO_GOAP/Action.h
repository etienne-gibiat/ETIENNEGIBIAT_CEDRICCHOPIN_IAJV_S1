#pragma once
#include <string>
#include <vector>
#include "World.h"

class Action
{
public:
	Action(const std::string nameAction, World& world): myAction(nameAction), parWorld(world) {};
	void AddEffect(const std::string effect);
	void AddPrecondition(const std::string effect, const bool isActiv);

private:

	std::string myAction;
	std::vector<std::string> listEffect;
	std::vector<std::string> listPrecondition;
	World& parWorld;
};