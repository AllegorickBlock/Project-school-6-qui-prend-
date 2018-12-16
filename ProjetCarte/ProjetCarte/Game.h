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
		Turn(Player * les_joueurs[], Game_Board& plateau, Deck& my_deck);
		~Turn();
	};

public:
	Game();
	~Game();

	static inline void Show_beef_symbol();
	static inline void Show_card(Card my_card);
	static inline void Show_deck(Deck &my_deck);
	static inline void Show_hand(Player * les_joueurs[]);
	static inline void Show_row(Game_Board & my_game_board);
	static inline void Show_cards_selection(Card * cards_selection[], Player * my_players[]); // Montre les cartes selectionné des joueurs pour 1 tour
	static inline void Show_player_scores(Player * my_players[]);

	static inline void Sort_asc(Card * my_tab[] ); // Trie dans l'ordre croissant un tableau de pointeurd de Card
	static inline void Sort_asc(int my_tab[]);	// Trie dans l'ordre croissant le contenu d'un tableau d'entier
	

	static inline void Pick_card_random(Card * cards_selec[], Player les_joueurs[]); // Fait choisir au joueurs aléatoirement leurs cartes
	static inline void Look_add_in_row(Game_Board & plateau, Card * cards_selection[], Player * my_players[]);
						// Ajoute dans les rangées la selections de carte du tour en respectant les regles du jeu
	inline void Start(Player * les_joueurs[], Game_Board& plateau, Deck& my_deck);
};
