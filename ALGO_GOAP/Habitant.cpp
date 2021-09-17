#include "Habitant.h"
#include "Evaluate.h"



void Habitant::DoSomething()
{
	ActionHabitant action;
	Evaluate eval;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator(seed);
	float random = generator() / static_cast<float>(generator.max());

	float evalWood = eval.Eval_Ressources(Ressource::Wood, world);
	float evalFood = eval.Eval_Ressources(Ressource::Food, world);

	if (random > capacity) {
		if (evalFood * 1.5 > evalWood) {
			action.Action_RecolteRessource(Ressource::Food, 2, world, this);
		}
		else {
			float randWood = generator() / static_cast<float>(generator.max());
			if (evalWood < randWood) {
				action.Action_CreationTabouret(world,this);
			}
			else {
				action.Action_RecolteRessource(Ressource::Wood, 3, world, this);
			}
			
		}
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
