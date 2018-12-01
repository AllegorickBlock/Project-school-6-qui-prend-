// ProjetCarte.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "iostream"
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include <fcntl.h>   // Bibliotheque necessaire pour l'utilisation de _setmode
#include <io.h>		 // Bibliotheque necessaire pour l'utilisation de _setmode

using namespace std;

static inline void Show_beef_symbol();

int main()
{
	Player les_joueurs[4];
	Row les_rangées[4];

	int point_arret;
	Deck my_deck;

	cout << " \n\n\n\n Deck non melangé \n\n\n\n ";
	for (int j = 0; j < 104; j++)
	{
		cout << "\n " << my_deck.Get_Card(j).Get_number() << "   " << my_deck.Get_Card(j).Get_beef_number();
		Show_beef_symbol();
	}

	my_deck.Mix_card();

	cout << " \n\n\n\n Deck melangé \n\n\n\n ";
	for (int j = 0; j < 104; j++)
	{
		cout << "\n " << my_deck.Get_Card(j).Get_number() << "   " << my_deck.Get_Card(j).Get_beef_number();
		Show_beef_symbol();
	}

	for (int i = 0; i < 4; i++)
	{
		my_deck.Add_card_to_player(les_joueurs[i]);
		my_deck.Add_card_to_row(les_rangées[i]);
	}

	cout << "\n\n\n Carte des joueurs : \n";

	for (int i = 0; i < 4; i++)
	{
		cout << "\n\t Joueur n°" << i << endl;
		for (int j = 0; j < 10; j++)
		{
			cout << les_joueurs[i].Get_hand_player().Get_card_of_hand(j).Get_number() << "   " << les_joueurs[i].Get_hand_player().Get_card_of_hand(j).Get_beef_number();
			Show_beef_symbol();
			cout << endl;
		}
	}

	cout << "\n\n\n Carte des rangées : \n";

	for (int i = 0; i < 4; i++)
	{
		cout << "\n\t Rangée n°" << i << endl;
		for (int j = 0; j < 6; j++)
		{
			if (&les_rangées[i].Get_card(j) != nullptr)
			{
				cout <<"["<< les_rangées[i].Get_card(j).Get_number() << " | " << les_rangées[i].Get_card(j).Get_beef_number();
				Show_beef_symbol();
				cout << "]   ";
			}
			else break;
		}
		cout << "\n\n\n\n";
	}



	cout << "\n\n\n\n Carte restante dans le Paquets \n\n ";

	int nbr_card_used = 0;
	for (int j = 0; j < 104; j++)
	{
		if ( ( my_deck.Get_Card(j).In_Deck() == true))
		{
			cout << "\n " << my_deck.Get_Card(j).Get_number() << "   " << my_deck.Get_Card(j).Get_beef_number();
			Show_beef_symbol();
			nbr_card_used++;
		}
	}

	cout << "\n\n Nombre de cartes restante dans le Paquets : " << nbr_card_used;

	cin >> point_arret;
}

static inline void Show_beef_symbol() // Affiche le symbole du zodiac du Taureau
{
	_setmode(_fileno(stdout), _O_U16TEXT); // Permet de passer au mode de translation de texte UTF16 pour indiquer les caracteres speciaux souhaite ( Voir doc : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?view=vs-2017 )
	wprintf(L"\x0222"); // Inscription en UTF16 du signe du zodiaque du taureau ( voir doc : https://www.compart.com/en/unicode/U+0222 ) 
	_setmode(_fileno(stdout), _O_TEXT);    // Necessaire pour eviter un plantage lors de la compilation : on reviens a l'etat normal de mode de translation de texte
}



