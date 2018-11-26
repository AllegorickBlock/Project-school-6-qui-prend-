#include "stdafx.h"
#include "Deck.h"



Deck::Deck()  // Constructeur par defaut qui reference chaque Carte � son adresse associ�e dans le tableau de carte
{
	for (int i = 0; i < 104; i++)
	{
		Card *my_Card = new Card(i+1); // On instancie dynamiquement une carte
		tab_Cards[i] = my_Card;		   // On dit a cette m�me carte qu'elle pointera vers tel adresse du tableau
	}
}


Deck::~Deck() // Destructeur necessaire pour detruire toutes les cartes cr�� dynamiquement, TRES IMPORTANT car il permet d'�viter un stackoverflow
{
	for (int i = 0; i < 104; i++)
	{
		delete tab_Cards[i];
		tab_Cards[i] = nullptr;
	}
}

Card Deck::Get_Card(int card_Number) { return *tab_Cards[card_Number]; }

void Deck::Mix_card()
{
	srand(time(0)); // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	int number_mix_cards[104];
	for (int i = 0; i < 104; i++) number_mix_cards[i] = 0; // On met toute les valeurs � 0 car par defaut les valeurs d'un tableau cr�� statiquement en C++ sont inconnue
	for (int i = 0; i < 104; i++) 
	{ 
		random_number = ((rand() % 104) + 1); // On aura ainsi un nombre aleatoire different a chaque fois que l'on entre dans la boucle
		number_mix_cards[i] = random_number;
		for (int j = 0; j < 104; j++)		  // Boucle verifiant si le numero de carte sorti n'a pas deja �t� attribu�
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
