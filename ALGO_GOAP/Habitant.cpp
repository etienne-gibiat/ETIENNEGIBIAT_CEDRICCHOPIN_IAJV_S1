#include "Habitant.h"



void Habitant::DoSomething()
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator(seed);
	float random = generator() / static_cast<float>(generator.max());

	if (random > capacity) {
		std::cout << "Habitant " << id << " recolte de la nourriture" << std::endl;
		world.nourritureDisponible += 2;
		world.nourritureDisponible = std::min(world.nourritureDisponible, world.nourritureMaximale);
		timeIdle = 0;
	}
	else {
		std::cout << "Habitant " << id << " patrouille.." << std::endl;
		timeIdle += 0.5;
	}
}

float Habitant::GetTimeIdle() const
{
	return timeIdle;
}

int Habitant::getId() const
{
	return id;
}
