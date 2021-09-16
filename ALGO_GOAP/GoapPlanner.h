#pragma once
#include <vector>
#include "Node.h"
#include "World.h"
class GoapPlanner
{

public:
	GoapPlanner(World& parWorld) : world(parWorld) {}
	void Init();
	void DeInit();
	//void MakeActionTree();
	std::vector<Action*> initPlan(Action* goal);
	bool buildTree(Node* node, std::vector<Node*>& leaves, Action* goal, std::vector<Action*> curentActionAvailble);
	bool checkPrecondition(std::vector<std::string> actionPrecondition, std::unordered_map<std::string, bool> parentState);
	std::unordered_map<std::string, bool> applyEffect(std::unordered_map<std::string, bool> parentState, std::vector<std::string> actionEffects);
	std::vector<Action*> removeAction(std::vector<Action*> curentActionAvailble, Action* action);
	bool checkPreconditionGoal(Action* goal, std::unordered_map<std::string, bool> curentState);


private:

	void aStar(Node* start);
	void showTree(Node* treeRoot, int index);
	void buildGraph(Node* parent);
	World& world;

	std::vector<Action*> AllActions;
};
