#pragma once
#include "Action.h"
#include <cassert>
#include <iostream>

void Action::AddEffect(const std::string& effect) {
	std::cout << "Add effect '" << effect << "' pour action : '" << myAction << "' " << std::endl;
	const auto effectIt = std::find(listEffect.begin(), listEffect.end(), effect);
	assert(effectIt == listEffect.end());
	if (effectIt != listEffect.end()) {
		return;
	}
	listEffect.push_back(effect);
}


void Action::AddPrecondition(const std::string& precondition, const bool isActiv) {
	std::cout << "Add precondition '" << precondition << "' pour action : '" << myAction << "' " << std::endl;
	

	const auto effectIt = std::find(listPrecondition.begin(), listPrecondition.end(), precondition);
	assert(effectIt == listPrecondition.end());
	if (effectIt != listPrecondition.end()) {
		return;
	}
	listPrecondition.push_back(precondition);

	const auto preconditionIt = parWorld.WorldPreconditions.find(precondition);
	if (preconditionIt != parWorld.WorldPreconditions.end()) {
		return;
	}
	std::cout << "Ajout de l'existence de la precondition " << precondition << " a la valeur " << isActiv << " dans le monde" << std::endl;
	parWorld.WorldPreconditions.insert(std::make_pair(precondition, isActiv));
}

std::vector<std::string> Action::getListEffect() const{
	return listEffect;
}

std::string Action::getMyAction() const{
	return myAction;
}

std::vector<std::string> Action::getListPrecondition() const{
	return listPrecondition;
}

int Action::getCost() const{

	return cost;
}
