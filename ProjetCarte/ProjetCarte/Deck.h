#pragma once
#include "Card.h"
#include "Player.h"
#include <ctime>   //Permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()
class Deck
{
	Card *tab_Cards[104]; // Pointeur renvoyant un tableau de differentes adresses ou l'on souhaitera stocker nos objets Card
	
public:
	Deck();
	~Deck();

	Card Get_Card(int card_Number);	   // Accesseur à l'objet Card de tab_Cards en fonction du parametre
	void Add_card_to_player(Player my_player);
	void Mix_card();
};

