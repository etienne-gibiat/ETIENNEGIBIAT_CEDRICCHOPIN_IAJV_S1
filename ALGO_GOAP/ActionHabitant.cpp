#include "ActionHabitant.h"
#include "Habitant.h"
#include "Espion.h"

void ActionHabitant::Action_RecolteRessource(Ressource ressource, unsigned int amount, World& world, Habitant* habitant)
{
	auto iterRessource = world.Stock.find(ressource);
	if (iterRessource != world.Stock.end()) {
		iterRessource->second.first = std::min(iterRessource->second.first + amount, iterRessource->second.second); // On ajoute la quantité de ressource jusqu'a un maximum de la capacité
		std::cout << "Habitant " << habitant->getId() << " recolte de la nourriture" << std::endl;
		habitant->SetTimeIdle(0);
	}
}

void ActionHabitant::Action_Patrouille(Habitant* habitant)
{
	std::cout << "Habitant " << habitant->getId() << " patrouille..." << std::endl;
	habitant->AddTimeIdle(0.5f);

}

void ActionHabitant::Action_CreationHabitant(const float moyEval, World& world)
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator(seed);
	float rand = generator() / static_cast<float>(generator.max()); // Generation d'un nombre random entre 0 et 1
	auto iterRessource = world.Stock.find(Ressource::Food);
	if (iterRessource == world.Stock.end()) {
		return;
	}

	if (rand < (moyEval) && iterRessource->second.first >= world.coutCreationHabitant) {
		world.nbHabitant++;
		float randEspion = generator() / static_cast<float>(generator.max()); // Generation d'un nombre random entre 0 et 1

		if (randEspion < 0.1f) {
			world.lstHabitant.push_back(new Espion(world, 0.8));
			iterRessource->second.second += world.coutCreationHabitant / 3; //Capacité maximale augmentée
			std::cout << " [[ Creation d'un espion, reduction de la nourriture ]] (" << iterRessource->second.first << ")" << std::endl;
		}
		else {
			world.lstHabitant.push_back(new Habitant(world, 0.6));
			iterRessource->second.second += world.coutCreationHabitant / 3; //Capacité maximale augmentée
			std::cout << " [[ Creation d'un habitant, reduction de la nourriture ]] (" << iterRessource->second.first << ")" << std::endl;
		}
		iterRessource->second.first -= world.coutCreationHabitant; // Creation d'un habitant - reduction des resources

		std::cout << "Nouvelle capacite maximale de nourriture : " << iterRessource->second.second << std::endl;

	}
}

