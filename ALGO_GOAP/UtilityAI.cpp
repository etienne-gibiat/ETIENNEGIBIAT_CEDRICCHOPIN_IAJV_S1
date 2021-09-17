#include "UtilityAI.h"
#include <iostream>
#include <numeric>
#include "Habitant.h"
#include "Espion.h"
#include "Evaluate.h"


float UtilityAI::EvaluationNourriture() const
{
	return  std::max((static_cast<float>(world.nourritureMaximale) - world.nourritureDisponible) / world.nourritureMaximale, static_cast <float>(0.0));
}

float UtilityAI::EvaluationCreationHabitantNombre() const
{
	float eval = exp2f(-2 * (world.nbHabitant / static_cast<float>(world.nbHabitantDesired)));
	//float eval = std::min(1 - (log10((world.nbHabitant * 2)) / static_cast<float>(world.nbHabitantDesired)) * 1.6, 1.0);
	return eval;
}

float UtilityAI::EvaluationTimeIdle(const float time) const
{

	float eval = std::max(exp2f(-0.1f * time),0.0f);
	return eval;
}
void UtilityAI::Tick(unsigned int const nbTurn)
{
	Evaluate eval;
	ActionHabitant action;
	Habitant* villageois = new Habitant(world, 0.3f); //Le village commence avec un habitant seul et malheureux
	world.lstHabitant.push_back(villageois);
	int i = nbTurn; //Nombre d'itérations du monde

	float totalTimeIdle;
	std::vector<float> listEval;
	while (i-- > 0) {
		totalTimeIdle = 0;
		listEval.clear();
		std::cout << "############################" << std::endl;
		for (Habitant* habit : world.lstHabitant) {
			habit->DoSomething();
			totalTimeIdle += habit->GetTimeIdle(); // On recupere la durée total d'idle de tout les habitants

		}
		float moyEval = eval.Eval_MoyCreationHabitant(totalTimeIdle, Ressource::Food, world); // Calcul de la moyenne des evaluations
		action.Action_CreationHabitant(moyEval, world);

		std::cout << "Stock actuel nourriture : " << world.Stock.at(Ressource::Food).first << " / " << world.Stock.at(Ressource::Food).second << std::endl;
		std::cout << "Stock actuel Bois : " << world.Stock.at(Ressource::Wood).first << " / " << world.Stock.at(Ressource::Wood).second << std::endl;
		std::cout << "############################" << std::endl;
	}
}

void UtilityAI::DeInit()
{
	//Libere les habitants de l'emprise de l'algorithme
	for (Habitant* habit : world.lstHabitant) {
		if (habit != nullptr) {
			delete habit;
			habit = nullptr;
		}
	}
}
