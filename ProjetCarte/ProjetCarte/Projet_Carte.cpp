// ProjetCarte.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "iostream"
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Game_Board.h"
#include "Game.h"
#include <fcntl.h>   // Bibliotheque necessaire pour l'utilisation de _setmode
#include <io.h>		 // Bibliotheque necessaire pour l'utilisation de _setmode

using namespace std;

static inline void Show_beef_symbol();

int main()
{
	int point_arret;

	Player les_joueurs[4];
	Game_Board plateau;
	Deck my_deck;

	Game * my_Game = new Game(les_joueurs, plateau, my_deck); // ON créée une partiue vie la constructeur de Game

	cin >> point_arret;
	delete my_Game;
	my_Game = nullptr;
}



