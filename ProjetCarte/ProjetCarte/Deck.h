#pragma once
#include "Card.h"
#include "Player.h"
#include "Game_Board.h"
#include <ctime>   //Permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()
class Deck
{
	const int nbr_deck_cards = 104;
	const int nbr_player_cards = 10;
	const int nbr_cards_in_rows = 6;
	Card *tab_Cards[104]; // Pointeur renvoyant un tableau de differentes adresses ou l'on souhaitera stocker nos objets Card
	
public:
	Deck();
	~Deck();

	Card& Get_Card(int card_Number);	   // Accesseur à l'objet Card de tab_Cards en fonction du parametre
	void Add_card_to_player(Player & my_player);
	void Add_card_to_row(Game_Board::Row & my_row);
	void Mix_card();
};

