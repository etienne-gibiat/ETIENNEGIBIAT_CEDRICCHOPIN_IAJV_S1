#pragma once
#include "Habitant.h"
class Espion : public Habitant
{
public:

	Espion(World& parWorld, const float capacityKill) : Habitant(parWorld,capacityKill) {}
	void DoSomething() override;
	void AttackPlayer();

	float GetTimeIdle() const;
};