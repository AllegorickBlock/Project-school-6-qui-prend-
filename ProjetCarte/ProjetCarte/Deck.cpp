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



void Deck::Mix_card()// Reprend les 104 cartes du jeux et les mellange
{
	srand(time(0));  // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	bool a = true;
	Card * tampon_deck_cards[104];
	for (int i = 0; i < 104; i++) tampon_deck_cards[i] = tab_Cards[i]; // On met toute les valeurs à 0 car par defaut les valeurs d'un tableau créé statiquement en C++ sont inconnue
	for (int i = 0; i < 104; i++) 
	{ 
		random_number = ((rand() % 104) + 1); // On aura ainsi un nombre aleatoire different a chaque fois que l'on entre dans la boucle
		
		for (int j = 0; j < 104; j++)		  // Boucle verifiant si le numero de carte sorti n'a pas deja été attribué
		{
			if ( (tampon_deck_cards[i] == tampon_deck_cards[j]) && (i != j) ) // Si le nombre aleatoire obtenu est deja choisi, on va recalculer un autre nombre aleatoire pour cette même carte
			{
				i--;
				a = false;
				break; // Permet d'eviter de continuer les boucles du for inutiles
			}
		}
		if (a == true) tab_Cards[i] = tampon_deck_cards[random_number];
	}
}
