#pragma once
#include "Action.h"
#include <cassert>

void Action::AddEffect(const std::string effect) {
	auto effectIt = parWorld.WorldPreconditions.find(effect);
	assert(effectIt == parWorld.WorldPreconditions.end());
	if (effectIt != parWorld.WorldPreconditions.end()) {
		return;
	}
	parWorld.WorldPreconditions.insert(std::make_pair(effect, this));
}


void Action::AddPrecondition(const std::string precondition) {
	auto preconditionIt = parWorld.WorldPreconditions.find(precondition);
	assert(preconditionIt == parWorld.WorldPreconditions.end());
	if (preconditionIt != parWorld.WorldPreconditions.end()) {
		return;
	}
	parWorld.WorldPreconditions.insert(std::make_pair(precondition,this));
}