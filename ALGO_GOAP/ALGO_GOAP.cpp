#include <iostream>
#include "World.h"
#include "Action.h"
#include "UtilityAI.h"
#include "Habitant.h"
#include "GoapPlanner.h"

unsigned int Habitant::idHabitant = 0;

int main()
{
	World world;
	GoapPlanner sm(world);

	sm.Init();
	
	sm.LetsGo();

	sm.DeInit();

	std::cout << "##### Algorithme UtilityAI #####" << std::endl;

	UtilityAI uAI(world);
	world.nourritureDisponible = 0;
	world.nourritureMaximale = 30;
	world.coutCreationHabitant = 15;
	world.nbHabitant = 1;
	world.nbHabitantDesired = 10;

	uAI.Tick();

	return 0;
	

}