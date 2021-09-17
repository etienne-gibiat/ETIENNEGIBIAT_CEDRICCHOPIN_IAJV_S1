#pragma once
#include "World.h"

class Espion;
class Habitant;
class ActionHabitant
{
public:

	void Action_RecolteRessource(Ressource ressource, unsigned int amount, World& world, Habitant* habitant);

	void Action_Patrouille(Habitant* habitant);

	void Action_CreationHabitant(const float moyEval, World& world);

};
