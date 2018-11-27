#include "stdafx.h"
#include "Player.h"


Player::Player() { this->main = new Player::Hand_Player; } // On cree dynamiquement notre objet main apparenté au joueur


Player::~Player() // Le destructeur va detruite l'instendce dynamique créé par le constructeur
{
	delete this->main;
	main = nullptr;
}

Player::Hand_Player Player::Get_hand_player()
{
	return *this->main;
}



//////////////////////////////CONSTRUCTEURS,DESTRUCTEURS ET FONCTIONS DE LA CLASSE INTERNE Hand_Player

Player::Hand_Player::Hand_Player()
{
}

Player::Hand_Player::~Hand_Player()
{
}

Card Player::Hand_Player::Get_card_of_hand(int card) // Gere les exceptions dans lesquelles on veut acceder à des cartes qui ne sont plus/pas dans la main du joueur
{
	if (this->player_Cards[card]->Get_number() != 0 && card < 10 && card >= 10) return *this->player_Cards[card];
	else throw "On essaye d'acceder a une carte de la main du joueur n'existant pas/plus !";
}

void Player::Hand_Player::Add_start_card(Deck game_deck)
{
	int hand_counter = 0;
	for (int i = 103; ((i > 0) && (hand_counter < 10)); i--) // On regarde toute les cartes du paquet et on va en soustraire j'usqu'à 10 pour les ajouter dans la main du joueur
	{
		if (&game_deck.Get_Card(i) != nullptr) // On regarde si les carte restantes dans le paquets
		{
			*this->player_Cards[hand_counter] = game_deck.Get_Card(i); // On attribue la VALEUR ET LE CONTENU de l'objet Card provenant de Get_card a la carte de main du joueur attribuée
			game_deck.Remove_card(i);
			hand_counter++;
		}
	}
}