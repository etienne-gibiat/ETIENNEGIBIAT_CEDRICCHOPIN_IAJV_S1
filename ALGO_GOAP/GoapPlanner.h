#pragma once
#include <vector>
#include "Node.h"
#include "World.h"
class GoapPlanner
{

public:
	GoapPlanner(World& parWorld) : world(parWorld) {}
	/// <summary>
	/// Initialise les pointeurs
	/// </summary>
	void Init();

	/// <summary>
	/// Desalloue les pointeurs
	/// </summary>
	void DeInit();

	/// <summary>
	/// Lancement de l'algorithme
	/// </summary>
	void LetsGo();

	/// <summary>
	/// Initialise les donn�es avant de construire le graph
	/// </summary>
	/// <param name="goal">But a atteindre</param>
	/// <returns></returns>
	std::vector<Action*> initPlan(Action* goal);


	/// <summary>
	/// Construction du graph
	/// </summary>
	/// <param name="node"></param>
	/// <param name="leaves"></param>
	/// <param name="goal"></param>
	/// <param name="curentActionAvailble"></param>
	/// <returns></returns>
	bool buildTree(Node* node, std::vector<Node*>& leaves, Action* goal,const std::vector<Action*>& curentActionAvailble);
	
	/// <summary>
	/// Verification de si les pr�conditions de l'action en param�tre sont d�j� valid�es
	/// </summary>
	/// <param name="actionPrecondition"></param>
	/// <param name="parentState"></param>
	/// <returns></returns>
	bool checkPrecondition(const std::vector<std::string>& actionPrecondition,const std::unordered_map<std::string, bool>& parentState) const;
	
	/// <summary>
	/// Applique les effets de l'action
	/// </summary>
	/// <param name="parentState"></param>
	/// <param name="actionEffects"></param>
	/// <returns></returns>
	std::unordered_map<std::string, bool> applyEffect(const std::unordered_map<std::string, bool>& parentState,const std::vector<std::string>& actionEffects) const;
	
	/// <summary>
	/// Enleve une action de la liste des actions disponibles
	/// </summary>
	/// <param name="curentActionAvailble"></param>
	/// <param name="action"></param>
	/// <returns></returns>
	std::vector<Action*> removeAction(const std::vector<Action*>& curentActionAvailble, Action* action) const;
	
	/// <summary>
	/// Renvois faux si une des pr�conditions du but n'est pas respect�e
	/// </summary>
	/// <param name="goal"></param>
	/// <param name="curentState"></param>
	/// <returns></returns>
	bool checkPreconditionGoal( Action* goal, std::unordered_map<std::string, bool>& const curentState) const;
	
	/// <summary>
	/// Renvois un bool�an al�atoire
	/// </summary>
	/// <returns></returns>
	bool randBool() const;

private:

	World& world;

	std::vector<Action*> AllActions;
};
