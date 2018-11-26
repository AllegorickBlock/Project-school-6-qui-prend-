// ProjetCarte.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "iostream"
#include "Deck.h"
#include "Card.h"
#include <fcntl.h>  // Bibliotheque necessaire pour l(utilisation de _setmode
#include <io.h> // Bibliotheque necessaire pour l(utilisation de _setmode

using namespace std;

static inline void Show_beef_symbol();

int main()
{
	int point_arret;
	cout << "\n\n\n tas de carte du jeu mit dans l'ordre par defaut : \n";
	Deck my_deck;
	for (int j = 0; j < 104; j++)
	{
		cout << "\n " << my_deck.Get_Card(j).Get_number() << "   " << my_deck.Get_Card(j).Get_beef_number();
		Show_beef_symbol();
	}
	cout << "\n\n\n Tas de carte du jeu apres avoir ete melange : \n";

	my_deck.Mix_card();

	for (int j = 0; j < 104; j++)
	{
		cout << "\n " << my_deck.Get_Card(j).Get_number() << "   " << my_deck.Get_Card(j).Get_beef_number();
		Show_beef_symbol();
	}

	cin >> point_arret;
}

static inline void Show_beef_symbol() // Affiche le symbole du zodiax du Taureau
{
	_setmode(_fileno(stdout), _O_U16TEXT); // Permet de passer au mode de translation de texte UTF16 pour indiquer les caracteres speciaux souhaite ( Voir doc : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?view=vs-2017 )
	wprintf(L" \x0222 "); // Inscription en UTF16 du signe du zodiaque du taureau ( voir doc : https://www.compart.com/en/unicode/U+0222 ) 
	_setmode(_fileno(stdout), _O_TEXT);    // Necessaire pour eviter un plantage lors de la compilation : on reviens a l'etat normal de mode de translation de texte
}



