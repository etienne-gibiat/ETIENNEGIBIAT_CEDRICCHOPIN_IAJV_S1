#pragma once
#include <unordered_map>

class Action;
struct World
{
	std::unordered_map<std::string, bool> WorldPreconditions;
};