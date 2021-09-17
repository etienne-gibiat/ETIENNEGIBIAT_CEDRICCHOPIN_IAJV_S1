#pragma once
#include <string>
#include <vector>
#include "World.h"

class Action
{
public:
	Action(const std::string& nameAction, World& world, int actionCost): myAction(nameAction), parWorld(world), cost(actionCost) {};
	void AddEffect(const std::string& effect);
	void AddPrecondition(const std::string& precondition, const bool isActiv);

	std::vector<std::string> getListEffect() const;
	std::string getMyAction() const;
	std::vector<std::string> getListPrecondition() const;
	int getCost() const;

private:

	int cost;
	std::string myAction;
	std::vector<std::string> listEffect;
	std::vector<std::string> listPrecondition;
	World& parWorld;
};