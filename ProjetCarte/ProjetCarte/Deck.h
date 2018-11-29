#pragma once
#include "Card.h"
#include <ctime>   //Permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()
class Deck
{
	Card *tab_Cards[104]; // Pointeur renvoyant un tableau de differentes adresses ou l'on souhaitera stocker nos objets Card
	
public:
	Deck();
	~Deck();

	Card Get_Card(int card_Number);	   // Accesseur à l'objet Card de tab_Cards en fonction du parametre
	void Remove_card(int card_Number); // On retire une carte du dack
	void Mix_card();
};

