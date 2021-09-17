#pragma once
#include "Node.h"

Node::Node(Node* parent, std::unordered_map<std::string, bool>& state, int cost, Action* action) {
	nodeParent = parent;
	curentState = state;
	curentCost = cost;
	nodeAction = action;
}

std::unordered_map<std::string, bool>& Node::getState(){

	return curentState;

}

Action* Node::getAction() const {

	return nodeAction;

}

int Node::getCost() const {
	return curentCost;
}

Node* Node::getParrent() const {
	return nodeParent;
}