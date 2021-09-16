#pragma once
#include "World.h"
class UtilityAI
{
public:
	UtilityAI(World& parWorld) : world(parWorld) {};
	/// <summary>
	/// Evaluation du besoin de nourriture 
	/// </summary>
	/// <returns></returns>
	float EvaluationNourriture() const;


	/// <summary>
	/// Evaluation par rapport au nombre actuel d'habitants et le nombre désiré
	/// </summary>
	/// <returns>Retourne le score normalisé</returns>
	float EvaluationCreationHabitantNombre() const;

	/// <summary>
	/// Evaluation du cout d'un habitant par rapport au temps que les habitants passent a rien faire
	/// </summary>
	/// <param name="time">Temps d'un villageois passer en idle</param>
	/// <returns>Retourne le score normalisé</returns>
	float EvaluationTimeIdle(const float time) const;


	/// <summary>
	/// Lance la simulation de l'algorithme
	/// </summary>
	void Tick();
private:
	World& world;

};