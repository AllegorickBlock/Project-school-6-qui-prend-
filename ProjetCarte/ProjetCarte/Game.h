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
		Card * cards_selection[4];

	public:
		static int  Get_gamer();
		Turn(Player les_joueurs[], Game_Board& plateau, Deck& my_deck);
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
	static inline void Sort_asc(Card * my_tab[]);
	static inline void Sort_asc(int my_tab[]);
	static inline void Pick_card_random(Card * cards_selec[], Player les_joueurs[]);
	static inline void Look_add_in_row(Game_Board & plateau, Card * cards_selection[] );
};
