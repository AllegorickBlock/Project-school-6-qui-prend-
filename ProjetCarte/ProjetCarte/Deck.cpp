#include "stdafx.h"
#include "Deck.h"



Deck::Deck()// Constructeur par defaut qui reference chaque Carte A son adresse associé dans le tableau de carte
{
	for (int i = 0; i < 104; i++)
	{
		Card *my_Card = new Card(i+1); // on instancie dynamiquement une carte
		tab_Cards[i] = my_Card; // On dit a cette même carte qu'elle pointera vers tel adresse du tableau
	}
}


Deck::~Deck() // Destructeur necessaire pour detruire toutes les carte créé dynamiquement, TRES IMPORTANT Car il permet d'éviter un stackoverflow
{
	for (int i = 0; i < 104; i++)
	{
		delete tab_Cards[i];
		tab_Cards[i] = nullptr;
	}
}

Card Deck::get_Card(int some_Card) { return *tab_Cards[some_Card]; }
void Deck::Mix_card()
{
	srand(time(0)); // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	Card *store_cards[104];
	for (int i = 0; i < 104; i++)
	{ 
		Card *my_card = new Card(i + 1);
		store_cards[i] = my_card;	
	}

	for (int j = 0; j < 104; j++)
	{
		random_number = ( (rand() % 104) + 1 );
		if (store_cards[random_number] != nullptr)
		{
			tab_Cards[j] = store_cards[random_number];
			delete store_cards[j];
			store_cards[random_number] = nullptr;
		}
		else j--;
	}
	delete[] store_cards;
}
