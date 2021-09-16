#include "GoapPlanner.h"
#include "Action.h"
#include "Node.h"
#include <random>
#include <iostream>
#include <functional>


void GoapPlanner::Init() {

	Action* reload = new Action("Reload", world, 1);
	Action* get_Ammo = new Action("GetAmmo", world, 2);
	Action* drink_VPotion = new Action("DrinkVPotion", world, 1);
	Action* attack_player = new Action("AttackPlayer", world, 1);
	Action* drink_EPotion = new Action("DrinkEPotion", world, 1);
	Action* get_EPotion = new Action("GetEPotion", world, 2);
	Action* get_vPotion = new Action("GetVPotion", world, 2);
	Action* sleep = new Action("sleep", world, 5);
	Action* move_to_player = new Action("MoveToPlayer", world, 5);
	Action* get_weapon = new Action("GetWeapon", world, 3);

	
	AllActions.push_back(reload);
	AllActions.push_back(get_Ammo);
	AllActions.push_back(drink_VPotion);
	AllActions.push_back(attack_player);
	AllActions.push_back(drink_EPotion);
	AllActions.push_back(get_EPotion);
	AllActions.push_back(get_vPotion);
	AllActions.push_back(sleep);
	AllActions.push_back(get_weapon);
	AllActions.push_back(move_to_player);

	reload->AddPrecondition("Avoir une arme", randBool());
	reload->AddPrecondition("Avoir des munitions", randBool());
	reload->AddEffect("Avoir arme charge");

	get_Ammo->AddEffect("Avoir des munitions");

	drink_VPotion->AddPrecondition("avoir une potion de vie", randBool());
	drink_VPotion->AddEffect("Avoir de la vie");

	attack_player->AddEffect("Tue la cible");
	attack_player->AddPrecondition("Avoir arme charge", randBool());
	attack_player->AddPrecondition("Avoir une arme", randBool());
	attack_player->AddPrecondition("Joueur a porter", randBool());
	attack_player->AddPrecondition("Avoir de l energie", randBool());

	drink_EPotion->AddPrecondition("avoir une potion d energie", randBool());
	drink_EPotion->AddEffect("Avoir de l energie");

	get_EPotion->AddEffect("avoir une potion d energie");

	get_vPotion->AddEffect("avoir une potion de vie");

	sleep->AddEffect("Avoir de la vie");
	sleep->AddEffect("Avoir de l energie");

	get_weapon->AddEffect("Avoir une arme");
	get_weapon->AddEffect("Avoir arme charge");

	move_to_player->AddPrecondition("Avoir de la vie", randBool());
	move_to_player->AddPrecondition("Avoir de l energie", randBool());
	move_to_player->AddEffect("Joueur a porter");

	

	std::vector<Action*> plan = initPlan(attack_player);

	std::cout << std::endl;

	std::cout << "goal : " << plan.back()->getMyAction() << std::endl;

	std::cout << std::endl;

	std::cout << "precondition : "  << std::endl;

	for (std::string temp : plan.back()->getListPrecondition()) {

		std::cout << "- " << temp << std::endl;

	}

	std::cout << std::endl;

	std::cout << "goal state precondition : " << std::endl;

	for (std::string temp : plan.back()->getListPrecondition()) {

		auto search = world.WorldPreconditions.find(temp);
		if (search != world.WorldPreconditions.end()) {
			std::cout << "- " << temp << " : " << search->second << std::endl;
		}

	}

	std::cout << std::endl;


	std::cout << "world state precondition : " << std::endl;

	for (std::pair<std::string, int> element : world.WorldPreconditions)
	{
		
			std::cout << "- " << element.first << " : " << element.second << std::endl;
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

bool GoapPlanner::randBool() {

	std::mt19937 rng(std::random_device{}());
	return std::uniform_int_distribution<>{ 0, 1 }(rng);

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

std::vector<Action*> GoapPlanner::initPlan(Action* goal) {

	std::vector<Node*> leaves;
	std::vector<Action*> result;


	Node* goalNode = new Node(nullptr, world.WorldPreconditions, 0, nullptr);
	bool found = buildTree(goalNode, leaves, goal, AllActions);

	if (!found) {
		return result;
	}
	else {
		if(result.size() == 0)
			result.push_back(goal);
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

	Node* node = cheapest;
	while (node != nullptr) {
		if (node->getAction() != nullptr) {
			result.insert(result.begin(), node->getAction());
		}
		node = node->getParrent();
	}

	if(result.back()->getMyAction() != goal->getMyAction())
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

				newState.insert_or_assign(search->first, true);

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

	if (!checkPreconditionGoal(goal, world.WorldPreconditions)) {

		for (Action* temp : curentActionAvailble) {



			if (checkPrecondition(temp->getListPrecondition(), node->getState())) {


				std::unordered_map<std::string, bool> curentState = applyEffect(node->getState(), temp->getListEffect());

				Node* childNode = new Node(node, curentState, node->getCost() + temp->getCost(), temp);

				if (checkPreconditionGoal(goal, curentState)) {


					leaves.push_back(childNode);
					foundOne = true;
				}
				else {


					std::vector<Action*> newActionAvailble = removeAction(curentActionAvailble, temp);
					bool found = buildTree(childNode, leaves, goal, newActionAvailble);
					if (found)
						foundOne = true;
				}

			}


		}
	}
	else {
		foundOne = true;
	}

	return foundOne;

}