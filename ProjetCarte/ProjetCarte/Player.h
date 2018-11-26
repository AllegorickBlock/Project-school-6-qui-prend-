#pragma once
#include "Card.h"
#include "Deck.h"
#include "Hand_Player.h"



class Player
{
	Hand_Player * hand;

public:
	Player();
	~Player();
	Hand_Player Get_hand_player(); // Accesseur pour le membre hand 

};

