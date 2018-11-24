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

Card Deck::Get_Card(int some_Card) { return *tab_Cards[some_Card]; }

void Deck::Mix_card()
{
	srand(time(0)); // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	int number_mix_cards[104];
	for (int i = 0; i < 104; i++) number_mix_cards[i] = 0; // On met toute les valeurs à 0 car par defaut les valeurs d'un tableau créé statiquement en C++ sont inconnue
	for (int i = 0; i < 104; i++) 
	{ 
		random_number = ((rand() % 104) + 1); // On aura ainsi un nombre aleatoir different a chaque fois que l'on entre dans la boucle
		number_mix_cards[i] = random_number;
		for (int j = 0; j < 104; j++) // Boucle verifiant si le numero de carte sorti n'a pas dgea été attribué
		{
			if ( (number_mix_cards[i] == number_mix_cards[j]) && (i != j) )
			{
				i--;
				break;
			}
		}
	}
	for (int i = 0; i < 104; i++) { *tab_Cards[i] = Card(number_mix_cards[i]); } // On inscrit le resultat du melange dans notre tableau de cartes
}
