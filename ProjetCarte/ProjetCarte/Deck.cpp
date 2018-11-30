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

Card Deck::Get_Card(int card_Number) // Renvoie une carte du paquet
{ 
	if(card_Number <104 && card_Number >= 0) return *tab_Cards[card_Number];
	else throw "On essaye de recuperer une carte du Deck inexistante";
}


void Deck::Remove_card(int card_Number) // Enleve une carte du paquet
{
	if (card_Number < 104 && card_Number >= 0) tab_Cards[card_Number]->Set_number(0); // Une carte est consid�r�e comme retir�e du paquet si son attribut "number" dans le paquet est �gal � 0 
	else throw "On essaye de retirer une carte du Deck inexistante";
}

void Deck::Mix_card()// Reprend les 104 cartes du jeux et les mellange
{
	srand(time(0));  // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	Card * tampon_deck_cards[104];
	for (int i = 0; i < 104; i++) tampon_deck_cards[i] = tab_Cards[i]; // On met toute les valeurs � 0 car par defaut les valeurs d'un tableau cr�� statiquement en C++ sont inconnue
	for (int i = 0; i < 104; i++) 
	{ 
		random_number = ((rand() % 104) + 1); // On aura ainsi un nombre aleatoire different a chaque fois que l'on entre dans la boucle
		tab_Cards[i] = tampon_deck_cards[random_number];
		for (int j = 0; j < 104; j++)		  // Boucle verifiant si le numero de carte sorti n'a pas deja �t� attribu�
		{
			if ( (tab_Cards[i] == tab_Cards[j]) && (i != j) ) // Si le nombre aleatoire obtenu est deja choisi, on va recalculer un autre nombre aleatoire pour cette m�me carte
			{
				i--;
				break; // Permet d'eviter de continuer les boucles du for inutiles
			}
		}
	}
}
