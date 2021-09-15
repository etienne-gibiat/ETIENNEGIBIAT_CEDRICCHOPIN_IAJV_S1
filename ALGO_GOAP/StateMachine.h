#pragma once
#include <vector>
#include "World.h"
class StateMachine
{

public:
	StateMachine(World& parWorld) : world(parWorld) {}
	void Init();
	void DeInit();
private:
	World& world;

	std::vector<Action*> AllActions;
};
