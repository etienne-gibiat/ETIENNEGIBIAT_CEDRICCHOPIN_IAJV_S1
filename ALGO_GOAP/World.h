#pragma once
#include <unordered_map>
#include <iostream>

class Action;
class Habitant;

enum class Ressource
{
	Food,
	Wood
};
struct World
{
	std::unordered_map<std::string, bool> WorldPreconditions; // Conditions du monde et valeurs associées

	unsigned int nourritureDisponible; // Nourriture actuellement disponible 
	unsigned int nourritureMaximale; // Capacité maximale de nourriture

	std::unordered_map<Ressource, std::pair<unsigned int, unsigned int>> Stock; // Stock de ressource du village (Ressource - actuel / maximum)

	unsigned int coutCreationHabitant; // Cout en nourriture pour la création d'un habitant
	unsigned int nbHabitant; // Nombre actuel d'habitant
	unsigned int nbHabitantDesired; // Nombre d'habitants désirés	

	std::vector<Habitant*> lstHabitant;  //Liste contenant tout les habitants
};