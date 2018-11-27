#pragma once
#include "Card.h"
#include "Deck.h"

class Player
{

	class Hand_Player // Classe interne a Player 
	{
		Card * player_Cards[10]; //Contenant des 10 cartes du joueur
	public:
		Hand_Player();
		~Hand_Player();
		Card Get_card_of_hand(int card);
		void Add_start_card(Deck&  game_deck);
	};

	Hand_Player * main; // Membre liant la classe Hand_Player au la classe Player

public:
	Player();
	~Player();
	Hand_Player Get_hand_player();

};

