#pragma once
#include "World.h"
#include "ActionHabitant.h"
#include "Evaluate.h"
#include <iostream>
#include <chrono>
#include <random>

class Habitant
{
public:

	static unsigned int idHabitant;


	Habitant(World& parWorld, const float capacityCollect) : world(parWorld), timeIdle(0), capacity(capacityCollect) { idHabitant++; id = idHabitant; }

	/// <summary>
	/// Permet à l'habitant de faire une action
	/// </summary>
	virtual void DoSomething();

	/// <summary>
	/// Recupere la duree total où l'habitant ne fais rien
	/// </summary>
	/// <returns></returns>
	virtual float GetTimeIdle() const;

	/// <summary>
	/// Definis le temps idle
	/// </summary>
	/// <param name="time"></param>
	virtual void SetTimeIdle(const float time);
	
	/// <summary>
	/// Recupere l'id du personnage
	/// </summary>
	/// <returns></returns>
	virtual unsigned int getId() const;

	/// <summary>
	/// Ajoute du temps d'idle
	/// </summary>
	/// <param name="time"></param>
	virtual void AddTimeIdle(const float time);
protected:
	unsigned int id;
	float timeIdle;
	float capacity;
	World& world;

};