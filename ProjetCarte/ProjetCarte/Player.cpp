#include "stdafx.h"
#include "Player.h"


Player::Player() { this->hand = new Hand_Player; } // On cree dynamiquement notre objet main apparent� au joueur


Player::~Player() // Le destructeur va detruite l'instendce dynamique cr�� par le constructeur
{
	delete this->hand;
	this->hand = nullptr;
}

Hand_Player Player::Get_hand_player() { return *this->hand; }
