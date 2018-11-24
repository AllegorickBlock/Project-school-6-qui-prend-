// ProjetCarte.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "iostream"
#include "Deck.h"
#include "Card.h"
#include <fcntl.h>  // Bibliotheque necessaire pour l(utilisation de _setmode
#include <io.h> // Bibliotheque necessaire pour l(utilisation de _setmode

using namespace std;

int main()
{
	int point_arret;
	
	Deck my_deck;
	for (int j = 0; j < 104; j++)
	{
		cout << my_deck.get_Card(j).Get_number() << "   " << my_deck.get_Card(j).Get_beef_number();
		_setmode(_fileno(stdout), _O_U16TEXT); // Permet de passer au mode de translation de texte UTF16 pour indiquer les characteres speciaux souhaité ( Voir doc : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?view=vs-2017 )
		wprintf(L" \x0222 \n"); // Inscription en UTF16 du signe du zodiaque du taureau ( voir doc : https://www.compart.com/en/unicode/U+0222 ) 
		_setmode(_fileno(stdout), _O_TEXT); // Necessaire pour eviter un plantage lors de la compilation : on reviens a l'etat normal de mode de translation de texte

	}

	my_deck.Mix_card();

	for (int j = 0; j < 104; j++)
	{
		cout << my_deck.get_Card(j).Get_number() << "   " << my_deck.get_Card(j).Get_beef_number();
		_setmode(_fileno(stdout), _O_U16TEXT); // Permet de passer au mode de translation de texte UTF16 pour indiquer les characteres speciaux souhaité ( Voir doc : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?view=vs-2017 )
		wprintf(L" \x0222 \n"); // Inscription en UTF16 du signe du zodiaque du taureau ( voir doc : https://www.compart.com/en/unicode/U+0222 ) 
		_setmode(_fileno(stdout), _O_TEXT); // Necessaire pour eviter un plantage lors de la compilation : on reviens a l'etat normal de mode de translation de texte

	}

	cin >> point_arret;
}



