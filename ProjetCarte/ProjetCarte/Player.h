#pragma once
#include "Card.h"
#include "Const_var.h"
#include "Game_Board.h"
#include <io.h>	
#include <ctime>   //Permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()

class Player
{
	Card * selection_card;
	int score;
	int number;
	class Hand_Player // Classe interne a Player 
	{
		Card * player_Cards[Const_Var::nmbr_cards_in_Hand]; // Contient les 10 pointeurs de cartes du joueur
	public:
		Hand_Player();
		~Hand_Player();
		Card& Get_card_of_hand(int card);	   // Affiche la main du joueur
		void Add_card(Card * my_card, int index); // Ajoute une carte a la main du joueur

		void Remove_card(int index);
		bool Card_in_hand(int index);
	};
	Hand_Player * hand; // Membre liant la classe Hand_Player a la classe Player

public:
	Player();
	~Player();
	Hand_Player& Get_hand_player(); // Accesseur pour le membre hand dans la classe Player
	void Add_to_number_score(int beef_score);
	int Get_score();

	virtual void Pick_selection_card(Card * selection_cards[]);
	virtual void Add_in_row(Game_Board & my_board, Card * card_selection[]);

	void Set_card_selection(Card * my_card);
	void Remove_card_selection(Card * my_card);
	Card * Get_card_selection();
	int Get_number();


	inline void Sort_asc(int my_tab[]);

};


class Bot_Player : public Player
{
public:
	void Pick_selection_card(Card * selection_cards[]);
	void Add_in_row(Game_Board & my_board, Card * card_selection[]);
};


class Human_Player : public Player
{
public:
	void Pick_selection_card(Card * selection_cards[]);
	void Add_in_row(Game_Board & my_board, Card * card_selection[]);
};







