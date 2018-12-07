#pragma once
#include "iostream"
#include <ctime>
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Game_Board.h"
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
	Game(Player les_joueurs[], Game_Board& plateau, Deck& my_deck);
	~Game();
	static inline void Show_beef_symbol();
	static inline void Show_deck(Deck &my_deck);
	static inline void Show_hand(Player les_joueurs[]);
	static inline void Show_row(Game_Board & my_game_board);
	static inline void Sort_asc(Card * my_tab[]);
	static inline void Sort_asc(int my_tab[]);
	static inline void Pick_card_random(Card cards_selection[], Player les_joueurs[]);
};

static struct Const_var
{
	static const int nmbr_cards_in_Hand = 10;
	static const int nmbr_Gamer = 4;
	static const int nmbr_Rows = 4;
	static const int nmbr_cards_in_Rows = 6;
	static const int nmbr_deck_cards = 104;
};
