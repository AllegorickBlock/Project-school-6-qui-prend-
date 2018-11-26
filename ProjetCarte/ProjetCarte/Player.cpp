#include "stdafx.h"
#include "Player.h"


Player::Player(Hand_Player hand)
{ this->hand = &hand; }


Player::~Player()
{
	delete this->hand;
	this->hand = nullptr;
}

Hand_Player Player::Get_hand_player() { return *this->hand; }
