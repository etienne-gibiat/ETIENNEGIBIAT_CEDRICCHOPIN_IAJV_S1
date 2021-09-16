#include "Espion.h"

void Espion::DoSomething()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator(seed);
	float random = generator() / static_cast<float>(generator.max());

	if (random > capacity) {
		AttackPlayer();
		timeIdle = 0;
	}
	else {
		std::cout << "Espion " << id << " patrouille.." << std::endl;
		timeIdle += 0.5;
	}
}

void Espion::AttackPlayer()
{

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, world.nbHabitant - 1); 
	int random = dist(rng);
	world.nbHabitant--;
	auto habitantToErase = world.lstHabitant.begin() + random;
	Habitant* h = *habitantToErase;
	std::cout << "L'espion " << id << " a tuer l'habitant " << h->getId() << std::endl;
	world.lstHabitant.erase(world.lstHabitant.begin() + random);
	
}

float Espion::GetTimeIdle() const
{
	return timeIdle;
}
