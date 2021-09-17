#include "ActionHabitant.h"
#include "Habitant.h"
#include "Espion.h"

void ActionHabitant::Action_RecolteRessource(Ressource ressource, unsigned int amount, World& world, Habitant* habitant)
{
	auto iterRessource = world.Stock.find(ressource);
	if (iterRessource != world.Stock.end()) {
		iterRessource->second.first = std::min(iterRessource->second.first + amount, iterRessource->second.second); // On ajoute la quantité de ressource jusqu'a un maximum de la capacité
		if (ressource == Ressource::Food) {
			std::cout << "Habitant " << habitant->getId() << " recolte de la nourriture" << std::endl;
		}
		else {
			std::cout << "Habitant " << habitant->getId() << " recolte du bois" << std::endl;
		}
		habitant->SetTimeIdle(0);
	}
}

void ActionHabitant::Action_Patrouille(Habitant* habitant)
{
	
	if (habitant->nbTabouret > 0) {
		std::cout << "Habitant " << habitant->getId() << " patrouille... il essaye de retrouver ses tabourets " << std::endl;
		habitant->AddTimeIdle(0.5f + (0.1f * habitant->nbTabouret) );
	}
	else {
		std::cout << "Habitant " << habitant->getId() << " patrouille..." << std::endl;
		habitant->AddTimeIdle(0.5f);
	}
	

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
			world.lstHabitant.push_back(new Espion(world, 0.8f));
			iterRessource->second.second += world.coutCreationHabitant / 3; //Capacité maximale augmentée
			std::cout << " [[ Creation d'un espion, reduction de la nourriture ]] (" << iterRessource->second.first << ")" << std::endl;
		}
		else {
			world.lstHabitant.push_back(new Habitant(world, 0.6f));
			iterRessource->second.second += world.coutCreationHabitant / 3; //Capacité maximale augmentée
			std::cout << " [[ Creation d'un habitant, reduction de la nourriture ]] (" << iterRessource->second.first << ")" << std::endl;
		}
		iterRessource->second.first -= world.coutCreationHabitant; // Creation d'un habitant - reduction des resources

		std::cout << "Nouvelle capacite maximale de nourriture : " << iterRessource->second.second << std::endl;

	}
}

void ActionHabitant::Action_CreationTabouret(World& world, Habitant* habitant)
{
	if (world.Stock.at(Ressource::Wood).first >= world.coutCreationTabouret) {
		world.Stock.at(Ressource::Wood).first -= world.coutCreationTabouret;
		habitant->nbTabouret++;
		std::cout << "Habitant " << habitant->getId() << " se creer un tabouret pour ses patrouilles puis le cache" << std::endl;
	}
	else {
		std::cout << "Oups... pas assez de bois, habitant " << habitant->getId() << " retourne chez lui bredouille"  << "(" << world.Stock.at(Ressource::Wood).first << "/ " << world.coutCreationTabouret << ")" << std::endl;
	}
}


