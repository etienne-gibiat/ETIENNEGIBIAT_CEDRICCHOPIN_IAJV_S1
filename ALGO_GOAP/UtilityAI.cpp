#include "UtilityAI.h"
#include <iostream>
#include <numeric>
#include "Habitant.h"
#include "Espion.h"
#include <chrono>
#include <random>


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

	float eval = std::max(exp2f(-0.1 * time), static_cast <float>(0.0));
	return eval;
}
void UtilityAI::Tick()
{
	
	Habitant* villageois = new Habitant(world,0.3); //Le village commence avec un habitant seul et malheureux
	world.lstHabitant.push_back(villageois);
	int i = 10; //Nombre d'itérations du monde
	float evalTimeIdle;
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

		evalTimeIdle = EvaluationTimeIdle(totalTimeIdle); // Evaluation en fonction de la duree total d'idle
		float evalNourriture = EvaluationNourriture();
		listEval.push_back(evalNourriture);
		
		std::cout << "Nourriture : " << world.nourritureDisponible << " , besoins de nouvelle nourriture : " << evalNourriture <<std::endl;
		
		float evalCreationH = EvaluationCreationHabitantNombre();
		std::cout << "Evaluation habitant en fonction du nombre : " << evalCreationH << std::endl;
		listEval.push_back(evalCreationH);
		listEval.push_back(evalCreationH); // La creation d'habitant en fonction du nombre possède un poids plus lourd 
		listEval.push_back(evalTimeIdle);
		std::cout << "eval timeidle : " << evalTimeIdle << std::endl;
		
		
		float sum = std::accumulate(listEval.begin(), listEval.end(), static_cast<float>(0.0)); // Somme de toutes les evaluations
		float moyEval = sum / static_cast<float>(listEval.size()); // Calcul de la moyenne des evaluations
		std::cout << "Besoin pour la creation d'un habitant (actuel : " << world.nbHabitant << " ) : " << moyEval << std::endl;
		
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::minstd_rand0 generator(seed);
		float rand = generator() / static_cast<float>(generator.max()); // Generation d'un nombre random entre 0 et 1
		if (rand < (moyEval) && world.nourritureDisponible >= world.coutCreationHabitant) {
			world.nbHabitant++;
			float randEspion = generator() / static_cast<float>(generator.max()); // Generation d'un nombre random entre 0 et 1
			
			if (randEspion < 0.1) {
				world.lstHabitant.push_back(new Espion(world, 0.8));
				world.nourritureMaximale += world.coutCreationHabitant / 3; //Capacité maximale augmentée
				std::cout << " [[ Creation d'un espion, reduction de la nourriture ]] (" << world.nourritureDisponible << ")" << std::endl;
			}
			else {
				world.lstHabitant.push_back(new Habitant(world, 0.6));
				world.nourritureMaximale += world.coutCreationHabitant / 3; //Capacité maximale augmentée
				std::cout << " [[ Creation d'un habitant, reduction de la nourriture ]] (" << world.nourritureDisponible << ")" << std::endl;
			}
			world.nourritureDisponible -= world.coutCreationHabitant; // Creation d'un habitant - reduction des resources
			
			std::cout << "Nouvelle capacite maximale de nourriture : " << world.nourritureMaximale << std::endl;

			std::cout << "############################" << std::endl;
		}
	}

	//Libere les habitants de l'emprise de l'algorithme
	for (Habitant* habit : world.lstHabitant) {
		if (habit != nullptr) {
			delete habit;
			habit = nullptr;
		}
	}
}
