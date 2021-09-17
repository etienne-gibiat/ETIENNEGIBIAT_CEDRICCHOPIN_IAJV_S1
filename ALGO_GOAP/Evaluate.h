#pragma once
#include "World.h"
class Evaluate
{
public:
	float Eval_Ressources(Ressource ressource, World& world) const;

	float EvaluationTimeIdle(const float time) const;

	float EvaluationCreationHabitantNombre(const World& world) const;

	float Eval_MoyCreationHabitant(const float time, Ressource ressource, World& world) const;

};