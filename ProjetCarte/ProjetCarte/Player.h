#pragma once
#include "Card.h"
#include "Const_var.h"
#include <ctime>   //Permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()
#include "Game.h"

class Player
{
	int score;
	class Hand_Player // Classe interne a Player 
	{
		Card * player_Cards[Const_Var::nmbr_cards_in_Hand]; // Contient les 10 pointeurs de cartes du joueur
	public:
		Hand_Player();
		~Hand_Player();
		Card& Get_card_of_hand(int card);	   // Affiche la main du joueur
		void Add_card(Card * my_card, int index); // Ajoute une carte a la main du joueur

		void Remove_card(int & index);
		bool Card_in_hand(int & index);
	};

	Hand_Player * hand; // Membre liant la classe Hand_Player a la classe Player

public:
	int nb_Player;
	Player();
	~Player();
	Hand_Player& Get_hand_player(); // Accesseur pour le membre hand dans la classe Player
	void Add_to_number_score(int beef_score);
	void Show_hand();
	virtual Card Choose_card_for_turn(Card  cards_selec[], int index_players[]);
	virtual void Choose_row_to_add_card();

	int Get_score();

};



class Human_Player : public Player
{
	Card Choose_card_for_turn(Card * cards_selec[], int index_players[]);
};
//
//class Bot_Player : public Player
//{
//	void Choose_card_for_turn(Card *cards_selec[], int index_players[]);
//};
