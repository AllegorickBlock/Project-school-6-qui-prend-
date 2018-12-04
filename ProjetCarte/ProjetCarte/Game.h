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
	
	const int number_Gamer = 4;
	int number_turn;
	class Turn
	{
		Card * cards_selection[6];
		const int nbr_hand_cards = 10;
		const int number_Gamer = 4;
		const int number_Row = 4;
		int number_Turn;

		Turn(Player les_joueurs[4], Game_Board& plateau, Deck& my_deck);
		~Turn();
		
	};

public:
	Game(Player les_joueurs[4], Game_Board& plateau, Deck& my_deck);
	~Game();
	static inline void Show_beef_symbol();
	static inline void Show_deck(Deck &my_deck);
	static inline void Show_hand(Player les_joueurs[4]);
	static inline void Show_row(Game_Board & my_game_board);
	static inline void Sort_asc(Card * my_tab[]);
};

