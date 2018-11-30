#include "stdafx.h"
#include "Deck.h"



Deck::Deck()  // Constructeur par defaut qui reference chaque Carte à son adresse associée dans le tableau de carte
{
	for (int i = 0; i < 104; i++)
	{
		Card *my_Card = new Card(i+1); // On instancie dynamiquement une carte
		tab_Cards[i] = my_Card;		   // On dit a cette même carte qu'elle pointera vers tel adresse du tableau
	}
}


Deck::~Deck() // Destructeur necessaire pour detruire toutes les cartes créé dynamiquement, TRES IMPORTANT car il permet d'éviter un stackoverflow
{
	for (int i = 0; i < 104; i++)
	{
		delete tab_Cards[i];
		tab_Cards[i] = nullptr;
	}
}

Card Deck::Get_Card(int card_Number) // Renvoie une carte du paquet
{ 
	if(card_Number <104 && card_Number >= 0) return *tab_Cards[card_Number];
}

void Deck::Add_card_to_player(Player & my_player)
{
	int hand_counter = 0;
	for (int i = 103; i > 0; --i) // On regarde toute les cartes du paquet et on va en soustraire jusqu'a 10 pour les ajouter dans la main du joueur
	{
		if (this->tab_Cards[i]->Get_status() == 0 && hand_counter < 10)
		{
			my_player.Get_hand_player().Add_card(*this->tab_Cards[i], i);
			hand_counter++;
		}
		else if (hand_counter == 10 ) break;
	}
}



void Deck::Mix_card()// Reprend les 104 cartes du jeux et les mellange
{
	srand(time(0));  // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	//bool a = true;
	Card * tampon_deck_cards[104];
	for (int i = 0; i < 104; i++) tampon_deck_cards[i] = nullptr; // On met toute les valeurs à 0 car par defaut les valeurs d'un tableau créé statiquement en C++ sont inconnue
	for (int i = 0; i < 104; i++) 
	{ 
		random_number = ((rand() % 104) + 1);
		tampon_deck_cards[i] = tab_Cards[random_number - 1];
		for (int j = 0; j < 104; j++)
		{
			if (tampon_deck_cards[i] == tampon_deck_cards[j] && (i != j))
			{
				--i;
				break;
			}
		 }
	}

	for (int i = 0; i < 104; i++) tab_Cards[i] = tampon_deck_cards[i];
}
