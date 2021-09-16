#include "GoapPlanner.h"
#include "Action.h"
#include "Node.h"
#include <iostream>
void GoapPlanner::Init() {

	Action* reload = new Action("Reload", world, 1);
	Action* attack_player = new Action("AttackPlayer", world, 1);
	Action* move_to_player = new Action("MoveToPlayer", world, 5);
	Action* get_weapon = new Action("GetWeapon", world, 3);
	AllActions.push_back(attack_player);
	AllActions.push_back(reload);
	AllActions.push_back(move_to_player);
	AllActions.push_back(get_weapon);
	
	reload->AddPrecondition("Avoir une arme",true);
	reload->AddEffect("Avoir des munitions");

	attack_player->AddEffect("Tue la cible");
	attack_player->AddPrecondition("Avoir des munitions",true);
	attack_player->AddPrecondition("Avoir une arme",false);
	attack_player->AddPrecondition("Joueur a porter",false);

	move_to_player->AddEffect("Joueur a porter");

	get_weapon->AddEffect("Avoir une arme");
	get_weapon->AddEffect("Avoir des munitions");

	std::vector<Action*> plan = initPlan(attack_player);

	std::cout << std::endl;

	std::cout << "goal : " << plan.back()->getMyAction() << std::endl;

	std::cout << std::endl;

	std::cout << "precondition : "  << std::endl;

	for (std::string temp : plan.back()->getListPrecondition()) {

		std::cout << "- " << temp << std::endl;

	}

	std::cout << std::endl;

	std::cout << "world state precondition : " << std::endl;

	for (std::string temp : plan.back()->getListPrecondition()) {

		auto search = world.WorldPreconditions.find(temp);
		if (search != world.WorldPreconditions.end()) {
			std::cout << "- " << temp  << " : " << search->second << std::endl;
		}

	}

	std::cout << std::endl;

	std::cout << "actions list to reach the goal : "  << std::endl;

	int count = 1;
	int totalCost = 0;

	for (Action* temp : plan) {

		std::cout << "- action " << count << " : " << temp->getMyAction() << std::endl;
		std::cout << "- cost : " << temp->getCost() << std::endl;
		std::cout << std::endl;

		count++;
		totalCost += temp->getCost();

	}
	std::cout << "- total cost : " << totalCost << std::endl;


}

void GoapPlanner::DeInit()
{
	for (Action* action : AllActions)
	{
		if (action != nullptr)
		{
			delete action;
			action = nullptr;
		}
	}

}

//void GoapPlanner::MakeActionTree() {
//
//	bool ok = false;
//
//	Action* actionTemp = AllActions.front();
//
//	Node* treeRoot = new Node(true, actionTemp->getMyAction());
//	Node* tempRoot = treeRoot;
//
//	buildGraph(treeRoot);
//
//	showTree(treeRoot, 0);
//	
//}

//void GoapPlanner::showTree(Node* treeRoot, int index) {
//
//	index++;
//	std::cout << "index : " << index << " node : " << treeRoot->getName() << " action : " << treeRoot->getIsAction() <<std::endl;
//
//	if (treeRoot->getChilds().size() > 0) {
//
//		for (Node* temp : treeRoot->getChilds()) {
//
//			showTree(temp, index);
//
//		}
//
//	}
//
//}

std::vector<Action*> GoapPlanner::initPlan(Action* goal) {

	std::vector<Node*> leaves;
	std::vector<Action*> result;


	Node* goalNode = new Node(nullptr, world.WorldPreconditions, 0, nullptr);
	bool found = buildTree(goalNode, leaves, goal, AllActions);

	if (!found) {
		return result;
	}

	Node* cheapest = nullptr;
	for(Node* leaf : leaves) {
		if (cheapest == nullptr)
			cheapest = leaf;
		else {
			if (leaf->getCost() < cheapest->getCost())
				cheapest = leaf;
		}
	}

	// get its node and work back through the parents
	Node* node = cheapest;
	while (node != nullptr) {
		if (node->getAction() != nullptr) {
			result.insert(result.begin(), node->getAction()); // insert the action in the front
		}
		node = node->getParrent();
	}

	result.push_back(goal);

	return result;

}

bool GoapPlanner::checkPrecondition(std::vector<std::string> actionPrecondition, std::unordered_map<std::string, bool> parentState) {

	bool ok = true;

	for (std::string temp : actionPrecondition) {

		auto search = parentState.find(temp);
		if (search != parentState.end()) {
			if (!search->second) {
				ok = false;
				break;
			}
		}

	}

	return ok;

}

std::unordered_map<std::string, bool> GoapPlanner::applyEffect(std::unordered_map<std::string, bool> parentState, std::vector<std::string> actionEffects) {
	
	std::unordered_map<std::string, bool> newState = parentState;
		

		for (std::string temp : actionEffects) {

			auto search = newState.find(temp);
			if (search != newState.end()) {

				newState.insert_or_assign(search->first, !search->second);

			}


		}

		return newState;
	
}

std::vector<Action*> GoapPlanner::removeAction(std::vector<Action*> curentActionAvailble, Action* action) {

	std::vector<Action*> newActionAvailble;

	for (Action* temp : curentActionAvailble) {

		if (temp->getMyAction() != action->getMyAction()) {

			newActionAvailble.push_back(temp);

		}

	}

	return newActionAvailble;
}

bool GoapPlanner::checkPreconditionGoal(Action* goal, std::unordered_map<std::string, bool> curentState) {

	bool ok = true;

	for (std::string temp : goal->getListPrecondition()) {
		auto search = curentState.find(temp);
		if (search != curentState.end()) {

			if (!search->second) {
				ok = false;
				break;
			}

		}
	}

	return ok;

}


bool GoapPlanner::buildTree(Node* node, std::vector<Node*>& leaves, Action* goal, std::vector<Action*> curentActionAvailble) {

	bool foundOne = false;

	for (Action* temp : curentActionAvailble) {

		// if the parent state has the conditions for this action's preconditions, we can use it here

		if (checkPrecondition(temp->getListPrecondition(), node->getState())) {

			// apply the action's effects to the parent state

			std::unordered_map<std::string, bool> curentState = applyEffect(node->getState(), temp->getListEffect());

			Node* childNode = new Node(node, curentState, node->getCost() + temp->getCost(), temp);

			if (checkPreconditionGoal(goal, curentState)) {
			
				// we found a solution!
				leaves.push_back(childNode);
				foundOne = true;
			}
			else {
				// not at a solution yet, so test all the remaining actions and branch out the tree

				std::vector<Action*> newActionAvailble = removeAction(curentActionAvailble, temp);
				bool found = buildTree(childNode, leaves, goal, newActionAvailble);
				if (found)
					foundOne = true;
			}

		}


	}

	return foundOne;

}


//
//void GoapPlanner::aStar(Node* start) {
//
//	std::vector<Node*> openNode;
//	openNode.push_back(start);
//
//	std::vector<std::string> preconditions;
//
//	for (Node* precondition : start->getChilds()) {
//
//		auto search = world.WorldPreconditions.find(precondition->getName());
//		if (search != world.WorldPreconditions.end()) {
//			if (!search->second) {
//				preconditions.push_back(precondition->getName());
//			}
//
//		}
//
//	}
//
//
//	while (openNode.size() > 0)
//	{
//		for (Node* node : openNode) {
//			openNode.erase(std::find(openNode.begin(), openNode.end(), node));
//			int min = 999999;
//			Node* minCostNode = nullptr;
//			for (Node* temp : node->getChilds())
//			{
//				if (temp->getCost() < min) {
//					min = temp->getCost();
//					minCostNode = temp;
//				}
//			}
//
//			bool ok = true;
//			std::vector<std::string> tempPreconditions = preconditions;
//
//			for (Node* precondition : minCostNode->getChilds()) {
//
//
//				auto search = world.WorldPreconditions.find(precondition->getName());
//				if (search != world.WorldPreconditions.end()) {
//					if (!search->second) {
//						ok = false;
//						tempPreconditions.push_back(search->first);
//					}
//
//				}
//
//			}
//
//			if (ok) {
//				for (Node* validatePrecondition : minCostNode->getChilds()) {
//
//				}
//			}
//			else {
//				
//
//
//				bool good = true;
//				for (Node* other : node->getChilds()) {
//					int nbPrecondition = 0;
//					if (other->getName() != minCostNode->getName()) {
//						for (Node* precondition : node->getChilds()) {
//
//
//							auto search = world.WorldPreconditions.find(precondition->getName());
//							if (search != world.WorldPreconditions.end()) {
//								if (!search->second) {
//									nbPrecondition++;
//								}
//
//							}
//
//						}
//
//						if ((preconditions.size() + nbPrecondition) < tempPreconditions.size()) {
//							good = false;
//							break;
//						}
//					}
//				
//				}
//
//				if (good) {
//					openNode.push_back(minCostNode);
//					preconditions = tempPreconditions;
//				}
//				else {
//
//				}
//
//			}
//		}
//	}
//
//
//}
//
//void GoapPlanner::buildGraph(Node* parent) {
//
//	if (parent->getIsAction()) {
//
//		int index = 0;
//		Action* parentAction = nullptr;
//		while (index < AllActions.size()) {
//
//			if (parent->getName() == AllActions.at(index)->getMyAction()) {
//				parentAction = AllActions.at(index);
//				index = AllActions.size();
//			}
//			index++;
//		}
//
//		if (parentAction == nullptr || parentAction->getListPrecondition().size() == 0) {
//			return;
//		}
//
//		for (const std::string temp : parentAction->getListPrecondition())
//		{
//			Node* precondition = new Node(false, temp);
//			buildGraph(precondition);
//			parent->addNode(precondition);
//		}
//
//	}
//	else {
//
//		for (const Action* temp : AllActions) {
//			for (const std::string tempy : temp->getListEffect()) {
//				if (parent->getName() == tempy) {
//
//					Node* action = new Node(true, temp->getMyAction());
//					buildGraph(action);
//					parent->addNode(action);
//					break;
//				}
//			}
//
//		}
//
//	}
//
//}