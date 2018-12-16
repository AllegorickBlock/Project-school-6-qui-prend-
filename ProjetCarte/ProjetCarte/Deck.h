#pragma once
#include "Const_var.h"
#include "Card.h"
#include "Player.h"
#include "Game_Board.h"
#include <ctime>   //Permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()
class Deck
{
	Card *tab_Cards[Const_Var::nmbr_deck_cards]; // Pointeur renvoyant un tableau de differentes adresses ou l'on souhaitera stocker nos objets Card
	
public:
	Deck();
	~Deck();

	Card& Get_Card(int card_Number);	   
	void Add_card_to_player(Player * my_player);
	void Add_card_to_row(Game_Board::Row & my_row);
	void Mix_card();
	void Recover_cards_and_mix(Player * my_player[] ,Game_Board * the_board);
};

