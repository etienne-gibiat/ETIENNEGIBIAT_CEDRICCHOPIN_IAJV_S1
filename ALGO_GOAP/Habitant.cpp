#include "Habitant.h"




void Habitant::DoSomething()
{
	ActionHabitant action;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator(seed);
	float random = generator() / static_cast<float>(generator.max());

	if (random > capacity) {
		action.Action_RecolteRessource(Ressource::Food, 2, world,this);
	}
	else {
		action.Action_Patrouille(this);
		
	}
}

float Habitant::GetTimeIdle() const
{
	return timeIdle;
}

void Habitant::AddTimeIdle(const float time) {

	timeIdle += time;
}

void Habitant::SetTimeIdle(const float time) {
	timeIdle = time;
}

unsigned int Habitant::getId() const
{
	return id;
}
