#pragma once
#include <unordered_map>

class Action;
class Habitant;
struct World
{
	std::unordered_map<std::string, bool> WorldPreconditions; // Conditions du monde et valeurs associées

	unsigned int nourritureDisponible; // Nourriture actuellement disponible 
	unsigned int nourritureMaximale; // Capacité maximale de nourriture

	unsigned int coutCreationHabitant; // Cout en nourriture pour la création d'un habitant
	unsigned int nbHabitant; // Nombre actuel d'habitant
	unsigned int nbHabitantDesired; // Nombre d'habitants désirés	

	std::vector<Habitant*> lstHabitant;  //Liste contenant tout les habitants
};