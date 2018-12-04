#pragma once
#include "iostream"
#include <ctime>
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Game_Board.h"
#include <fcntl.h>   // Bibliotheque necessaire pour l'utilisation de _setmode
#include <io.h>	

class Game
{
	Deck my_deck;
	int number_turn;

	int number_Gamer;
	class Turn
	{
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
};

