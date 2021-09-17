#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Action.h"

class Node
{
public:
    Node(Node* parent, std::unordered_map<std::string, bool>& state, int cost, Action* action);

    std::unordered_map<std::string, bool>& getState();
    Action* getAction();
    int getCost();
    Node* getParrent();

private:


    int curentCost;
    Action* nodeAction;
    Node* nodeParent;
    std::unordered_map<std::string, bool> curentState;
};