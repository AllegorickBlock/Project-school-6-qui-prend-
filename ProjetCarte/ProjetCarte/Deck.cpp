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
		//delete tab_Cards[i];
		tab_Cards[i] = nullptr;
	}
}

Card Deck::Get_Card(int card_Number) // ajoute une carte au paquet
{ 
	if(card_Number <104 && card_Number >= 0) return *tab_Cards[card_Number];
	else throw "On essaye de recuperer une carte du Deck inexistante";
}


void Deck::Remove_card(int card_Number) // Enleve une carte du paquet
{
	if (card_Number < 104 && card_Number >= 0)
	{
		tab_Cards[card_Number]->Set_number(0); // une carte est considéré comme retirée du paquet si sont attributs "number" dans le paquet est égal à 0 /!\ A AMELIORER SI POSSIBLE
	}
	else throw "On essaye de retirer une carte du Deck inexistante";
}

void Deck::Mix_card()// Reprend les 104 cartes du jeux et les mellanges
{
	srand(time(0)); // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	int number_mix_cards[104];
	for (int i = 0; i < 104; i++) number_mix_cards[i] = 0; // On met toute les valeurs à 0 car par defaut les valeurs d'un tableau créé statiquement en C++ sont inconnue
	for (int i = 0; i < 104; i++) 
	{ 
		random_number = ((rand() % 104) + 1); // On aura ainsi un nombre aleatoire different a chaque fois que l'on entre dans la boucle
		number_mix_cards[i] = random_number;
		for (int j = 0; j < 104; j++)		  // Boucle verifiant si le numero de carte sorti n'a pas deja été attribué
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
