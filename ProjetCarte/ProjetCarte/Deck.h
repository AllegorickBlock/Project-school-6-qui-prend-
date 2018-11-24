#pragma once
#include "Card.h"
#include <ctime> //permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()
class Deck
{
	Card *tab_Cards[104]; // Pointeur renvoyant un tableau de differentes adresse ou l'on souhaitera stoquer nos objets Card
	
public:
	Deck();
	~Deck();

	Card get_Card(int some_Card); // Accesseur à l'objet Card de tab_Cards en fonction du parametre
	void Mix_card();
};

