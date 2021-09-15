#include <iostream>
#include "World.h"
#include "Action.h"
#include "StateMachine.h"
int main()
{
	World world;
	StateMachine sm(world);

	sm.Init();


	sm.DeInit();

	return 0;
	

}