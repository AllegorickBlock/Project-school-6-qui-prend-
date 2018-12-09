#pragma once
#include "iostream"
#include "Const_var.h"
#include "Player.h"
#include "Game_Board.h"
#include "Card.h"
#include "Deck.h"
#include <ctime>
#include <fcntl.h>   // Bibliotheque necessaire pour l'utilisation de _setmode
#include <io.h>	
#include <ctime>   //Permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()

class Game
{
	
	class Turn
	{
		Card * cards_selection[Const_var::nmbr_Gamer];
		int index_player_selection[Const_var::nmbr_Gamer];

	public:
		Turn(Player les_joueurs[], Game_Board& plateau, Deck& my_deck, Card * offside_deck[]);
		~Turn();
	};

public:
	Game();
	~Game();
	static inline void Show_beef_symbol();
	static inline void Show_deck(Deck &my_deck);
	static inline void Show_hand(Player les_joueurs[]);
	static inline void Show_row(Game_Board & my_game_board);
	static inline void Show_cards_selection(Card * cards_selection[]);
	static inline void Show_player_scores(Player my_players[]);
	static inline void Show_offside_deck(Card * offside_deck[]);
	static inline void Sort_asc(Card * my_tab[] , int index_players[]);
	static inline void Sort_asc(int my_tab[]);
	static inline void Pick_card_random(Card * cards_selec[], Player les_joueurs[], int index_players[]);
	static inline void Look_add_in_row(Game_Board & plateau, Card * cards_selection[], Player my_players[], int index_players[], Card * offside_deck[]);
	static inline void Add_card_in_offside_deck(Game_Board::Row & my_row, Card * offside_deck[]);
};
