// ProjetCarte.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "iostream"
#include "Deck.h"
#include "Card.h"

using namespace std;

int main()
{
	Deck my_deck;
	for (int j = 0; j < 104; j++)
	{

		cout << my_deck.get_Card(j).Get_number() <<  endl;
	}
}



