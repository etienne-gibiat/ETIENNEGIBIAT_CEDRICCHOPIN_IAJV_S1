#include <iostream>
#include "World.h"
#include "Action.h"
#include "GoapPlanner.h"
int main()
{
	World world;
	GoapPlanner sm(world);

	sm.Init();


	sm.DeInit();

	return 0;
	

}