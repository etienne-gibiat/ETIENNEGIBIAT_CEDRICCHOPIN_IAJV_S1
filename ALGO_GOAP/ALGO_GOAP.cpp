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
	world.Stock.insert(std::make_pair(Ressource::Food, std::make_pair(0,30)));
	world.Stock.insert(std::make_pair(Ressource::Wood, std::make_pair(0,100)));
	world.nourritureDisponible = 0;
	world.nourritureMaximale = 30;
	world.coutCreationHabitant = 15;
	world.coutCreationTabouret = 33;
	world.nbHabitant = 1;
	world.nbHabitantDesired = 10;

	uAI.Tick(100);
	uAI.DeInit();

	return 0;
	

}