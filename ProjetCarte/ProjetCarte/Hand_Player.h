#pragma once
#include "Card.h"
#include "Deck.h"
#include "Player.h"

class Hand_Player
{
	Card * player_Cards[10]; //Contenant des 10 cartes du joueur
public:
	Hand_Player();
	~Hand_Player();
	Card Get_card_of_hand(int card);
	void Add_start_card(Deck game_deck);
};

