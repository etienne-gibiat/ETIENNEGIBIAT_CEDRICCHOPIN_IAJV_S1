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
	std::unordered_map<std::string, bool> WorldPreconditions; // Conditions du monde et valeurs associ�es

	unsigned int nourritureDisponible; // Nourriture actuellement disponible 
	unsigned int nourritureMaximale; // Capacit� maximale de nourriture

	std::unordered_map<Ressource, std::pair<unsigned int, unsigned int>> Stock; // Stock de ressource du village (Ressource - actuel / maximum)

	unsigned int coutCreationHabitant; // Cout en nourriture pour la cr�ation d'un habitant
	unsigned int nbHabitant; // Nombre actuel d'habitant
	unsigned int nbHabitantDesired; // Nombre d'habitants d�sir�s	

	std::vector<Habitant*> lstHabitant;  //Liste contenant tout les habitants
};