#include "stdafx.h"
#include "Player.h"

#pragma region Classe Player

#pragma region Player : Constructeur & Destructeur
Player::Player() 
{ 
	this->hand = new Player::Hand_Player();
	this->score = 0;

} // On cree dynamiquement notre objet main apparente au joueur

Player::~Player() // Le destructeur va detruite l'instance dynamique cree par le constructeur
{
	delete this->hand;
	hand = nullptr;
}
#pragma endregion

Player::Hand_Player& Player::Get_hand_player() { return *this->hand; }

void Player::Add_to_number_score(int beef_score)
{
	this->score += beef_score;
}

int Player::Get_score()
{
	return this->score;
}




#pragma endregion

#pragma region Classe Player::Hand_Player

#pragma region Player::Hand_Player : Constructeur & Destructeur
Player::Hand_Player::Hand_Player() { } 

Player::Hand_Player::~Hand_Player() {} 

#pragma endregion

void Player::Hand_Player::Add_card(Card * my_card, int index) // ON DOIT FAIRE UN PASSAGE PAR REFERENCE OU SINON LE DECK NE SE VERRA PAS MODIFIE -> CAR COPIE
{
	player_Cards[index] = my_card;
	player_Cards[index]->Set_status(1);
}


void Player::Hand_Player::Remove_card(int & index)
{
	this->player_Cards[index] = nullptr;
}

bool Player::Hand_Player::Card_in_hand(int & index)
{
	if (this->player_Cards[index] == nullptr) return false;
	else return true;
}

Card& Player::Hand_Player::Get_card_of_hand(int card) // Gere les exceptions dans lesquelles on veut acceder a des cartes qui ne sont plus/pas dans la main du joueur
{
	if (this->player_Cards[card]->Get_number() != 0 && card < Const_Var::nmbr_cards_in_Hand && card >= 0) return *player_Cards[card];
	else throw "On essaye d'acceder a une carte de la main du joueur n'existant pas/plus !";
}

#pragma endregion