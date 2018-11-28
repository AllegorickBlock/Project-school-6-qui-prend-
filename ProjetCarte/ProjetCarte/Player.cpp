#include "stdafx.h"
#include "Player.h"


Player::Player() { this->main = new Player::Hand_Player; } // On cree dynamiquement notre objet main apparente au joueur

Player::~Player() // Le destructeur va detruite l'instance dynamique cree par le constructeur
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
	for (int i = 0; i < 10; i++) this->player_Cards[i] = new Card(0);  //Cree le tableau de la main du joueur
}

Player::Hand_Player::~Hand_Player()
{
	for (int i = 0; i < 10; i++)
	{
		//delete this->player_Cards[i];
		this->player_Cards[i] = nullptr;
	}
}

void Player::Hand_Player::Add_start_card(Deck& game_deck) // ON DOIT FAIRE UN PASSAGE PAR REFERENCE OU SINON LE DECK NE SE VERRA PAS MODIFIE -> CAR COPIE
{
	int hand_counter = 0;
	for (int i = 103; i > 0 ; --i) // On regarde toute les cartes du paquet et on va en soustraire jusqu'a 10 pour les ajouter dans la main du joueur
	{
		if ( game_deck.Get_Card(i).Get_number() != 0 && (hand_counter < 10)) // /!\ game_deck.Get_Card(i).Get_number() != 0 est utilisé pour voir si la carte a ete rentre ou pas (voir Deck.Remove_card(i) ) A ameliorer si possible
		{
			*this->player_Cards[hand_counter] = game_deck.Get_Card(i); // On attribue la VALEUR ET LE CONTENU de l'objet Card provenant de Get_card a la carte de main du joueur attribue
			game_deck.Remove_card(i);
			hand_counter++;
		}
	}
}

Card Player::Hand_Player::Get_card_of_hand(int card) // Gere les exceptions dans lesquelles on veut acceder a des cartes qui ne sont plus/pas dans la main du joueur
{
	if (this->player_Cards[card]->Get_number() != 0 && card < 10 && card >= 0) return *this->player_Cards[card];
	else throw "On essaye d'acceder a une carte de la main du joueur n'existant pas/plus !";
}

