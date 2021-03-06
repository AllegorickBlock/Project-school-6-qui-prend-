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
	bool end;
	class Turn
	{
		Card * cards_selection[Const_Var::nmbr_Gamer]; // cartes selectionné des joueurs pour 1ce tour

	public:
		Turn(Player * the_players[], Game_Board& game_board, Deck& my_deck);
		~Turn();
	};

public:
	Game(int nb_human_player);
	~Game();

	static inline void Show_beef_symbol();
	static inline void Show_card(Card my_card);
	static inline void Show_deck(Deck &my_deck);
	static inline void Show_hand(Player * my_player);
	static inline void Show_row(Game_Board & my_game_board);
	static inline void Show_cards_selection(Player * my_players[], Card * selection_card[]); // Montre les cartes selectionné des joueurs pour 1 tour
	static inline void Show_player_scores(Player * my_players[]);

	static inline void Sort_asc(Card * my_tab[] ); // Trie dans l'ordre croissant un tableau de pointeurd de Card
	
	inline void Start(Player * the_players[], Game_Board& game_board, Deck& my_deck);
};
