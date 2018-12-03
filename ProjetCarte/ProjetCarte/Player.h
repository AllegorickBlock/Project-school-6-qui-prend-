#pragma once
#include "Card.h"

class Player
{
	class Hand_Player // Classe interne a Player 
	{
		const int nbr_player_cards = 10;
		Card * player_Cards[10]; // Contient les 10 pointeurs de cartes du joueur
	public:
		Hand_Player();
		~Hand_Player();
		Card& Get_card_of_hand(int card);	   // Affiche la main du joueur
		void Add_card(Card * my_card, int index); // Ajoute une carte a la main du joueur
	};

	Hand_Player * hand; // Membre liant la classe Hand_Player a la classe Player

public:
	Player();
	~Player();
	Hand_Player& Get_hand_player(); // Accesseur pour le membre hand dans la classe Player

};

