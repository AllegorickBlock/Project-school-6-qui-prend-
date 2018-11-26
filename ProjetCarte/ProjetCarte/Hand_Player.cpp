#include "stdafx.h"
#include "Hand_Player.h"


Hand_Player::Hand_Player()
{
}


Hand_Player::~Hand_Player()
{
}

Player Hand_Player::Get_player() { return *this->player; }

Card Hand_Player::Get_card_of_hand(int card) // Gere les exceptions dans lesquelles on veut acceder à des cartes qui ne sont plus/pas dans la main du joueur
{
	if(this->player_Cards[card]->Get_number() != 0 && card < 10 && card >= 10) return *this->player_Cards[card];
	else throw "On essaye d'acceder a une carte de la main du joueur n'existant pas/plus !";  
}
