#pragma once
#include <unordered_map>

struct World
{
	std::unordered_map<std::string, Action*> WorldPreconditions;
	std::unordered_map<std::string, Action*> WorldEffects;
};