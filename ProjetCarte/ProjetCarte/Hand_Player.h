#pragma once
#include "Card.h"
#include "Deck.h"
#include "Player.h"

class Hand_Player
{
	Player * player; // refere au joueur apparenté
	Card * player_Cards[10]; //Contenant des 10 cartes du joueur
public:
	Hand_Player();
	~Hand_Player();
	Player Get_player();
	Card Get_card_of_hand(int card);
};

