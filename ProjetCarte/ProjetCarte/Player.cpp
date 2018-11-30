#include "stdafx.h"
#include "Player.h"


Player::Player() { this->hand = new Player::Hand_Player(); } // On cree dynamiquement notre objet main apparente au joueur

Player::~Player() // Le destructeur va detruite l'instance dynamique cree par le constructeur
{
	delete this->hand;
	hand = nullptr;
}

Player::Hand_Player Player::Get_hand_player() { return *this->hand; }



//////////////////////////////CONSTRUCTEURS,DESTRUCTEURS ET FONCTIONS DE LA CLASSE INTERNE Hand_Player

Player::Hand_Player::Hand_Player() { for (int i = 0; i < 10; i++) this->player_Cards[i] = new Card(0); } //Cree le tableau de la main du joueur 

Player::Hand_Player::~Hand_Player() // Pas besoin d'effacer les objets Hand Player car on les effacera en même temps que Player, dans son destructeur
{}

void Player::Hand_Player::Add_card(Card * my_card, int index) // ON DOIT FAIRE UN PASSAGE PAR REFERENCE OU SINON LE DECK NE SE VERRA PAS MODIFIE -> CAR COPIE
{
	this->player_Cards[index] = my_card;
	this->player_Cards[index]->Set_status(1);

}

Card Player::Hand_Player::Get_card_of_hand(int card) // Gere les exceptions dans lesquelles on veut acceder a des cartes qui ne sont plus/pas dans la main du joueur
{
	if (this->player_Cards[card]->Get_number() != 0 && card < 10 && card >= 0)return *player_Cards[card];
	else throw "On essaye d'acceder a une carte de la main du joueur n'existant pas/plus !";
}

