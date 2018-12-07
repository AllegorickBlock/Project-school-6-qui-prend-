#pragma once
#include "Card.h"
#include <ctime>   //Permet d'utiliser time()
#include <cstdlib> //Permet d'utiliser srand()
#include "Game.h"

class Player
{
public:
	class Hand_Player // Classe interne a Player 
	{
		
		Card * player_Cards[Const_var::nmbr_cards_in_Hand]; // Contient les 10 pointeurs de cartes du joueur
	public:
		Hand_Player();
		~Hand_Player();
		Card& Get_card_of_hand(int card);	   // Affiche la main du joueur
		void Add_card(Card * my_card, int index); // Ajoute une carte a la main du joueur
		void Pick_card_random(Card cards_selection[],Player les_joueurs[]);

		void Remove_card(int & index);
		bool Card_in_hand(int & index);
	};

	Hand_Player * hand; // Membre liant la classe Hand_Player a la classe Player

public:
	Player();
	~Player();
	Hand_Player& Get_hand_player(); // Accesseur pour le membre hand dans la classe Player

};

